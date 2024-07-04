#include "PluginProcessor.h"
#include "PluginEditor.h"

/*static*/ const double PluginProcessor::BAND_DB_RAMP_TIME_SECONDS  = 0.02;
/*static*/ const double PluginProcessor::METER_DB_RAMP_TIME_SECONDS = 0.2;

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::PluginProcessor()
    : AudioProcessor(
        BusesProperties()
            .withInput(Global::Channels::getName(Global::Channels::PRIMARY_LEFT), juce::AudioChannelSet::mono(), true)
            .withInput(Global::Channels::getName(Global::Channels::PRIMARY_RIGHT), juce::AudioChannelSet::mono(), true)
            .withInput(Global::Channels::getName(Global::Channels::SIDECHAIN_LEFT), juce::AudioChannelSet::mono(), true)
            .withInput(Global::Channels::getName(Global::Channels::SIDECHAIN_RIGHT), juce::AudioChannelSet::mono(), true)
            .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , apvts_(*this, nullptr, "APVTS", getParameterLayout())
    , input_analysis_filter_()
    , band_updater_(input_analysis_filter_, band_db_values_)
{
}

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::~PluginProcessor()
{
}

/*---------------------------------------------------------------------------
**
*/
const juce::String
PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::acceptsMidi() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::producesMidi() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::isMidiEffect() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
double
PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

/*---------------------------------------------------------------------------
**
*/
int
PluginProcessor::getNumPrograms()
{
    return 1;  // NB: some hosts don't cope very well if you tell them there are 0 programs,
               // so this should be at least 1, even if you're not really implementing programs.
}

/*---------------------------------------------------------------------------
**
*/
int
PluginProcessor::getCurrentProgram()
{
    return 0;
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

/*---------------------------------------------------------------------------
**
*/
const juce::String
PluginProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::changeProgramName(int index, const juce::String& new_name)
{
    juce::ignoreUnused(index, new_name);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::prepareToPlay(double sample_rate, int samples_per_block)
{
    //
    // Pre-playback initialisation.
    //

    // EQ band dB values.
    for (auto& band : band_db_values_) {
        band.reset(sample_rate, BAND_DB_RAMP_TIME_SECONDS);
        band.setCurrentAndTargetValue(0.f);
    }

    // Input analysis filter.
    juce::dsp::ProcessSpec analysis_spec;

    analysis_spec.sampleRate       = sample_rate;
    analysis_spec.maximumBlockSize = samples_per_block;
    analysis_spec.numChannels      = getTotalNumInputChannels();

    input_analysis_filter_.prepare(analysis_spec);

    // FFT buffers.
    fft_buffers_.at(Global::FFT::PRIMARY_LEFT_PRE_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_PRE_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::PRIMARY_LEFT_POST_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_POST_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::SIDECHAIN_LEFT).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::SIDECHAIN_RIGHT).prepare(sample_rate);

    // Filter chains.
    juce::dsp::ProcessSpec filter_chain_spec;

    filter_chain_spec.sampleRate       = sample_rate;
    filter_chain_spec.maximumBlockSize = samples_per_block;
    filter_chain_spec.numChannels      = 1;

    filter_chain_left_.prepare(filter_chain_spec);
    filter_chain_right_.prepare(filter_chain_spec);

    // Band pass filters.
    updateFilterCoefficients();

    // Meter values.
    peak_l_.reset(sample_rate, METER_DB_RAMP_TIME_SECONDS);
    peak_r_.reset(sample_rate, METER_DB_RAMP_TIME_SECONDS);
    rms_l_.reset(sample_rate, METER_DB_RAMP_TIME_SECONDS);
    rms_r_.reset(sample_rate, METER_DB_RAMP_TIME_SECONDS);
    lufs_l_.reset(sample_rate, METER_DB_RAMP_TIME_SECONDS);
    lufs_r_.reset(sample_rate, METER_DB_RAMP_TIME_SECONDS);

    peak_l_.setCurrentAndTargetValue(Global::METER_NEG_INF);
    peak_r_.setCurrentAndTargetValue(Global::METER_NEG_INF);
    rms_l_.setCurrentAndTargetValue(Global::METER_NEG_INF);
    rms_r_.setCurrentAndTargetValue(Global::METER_NEG_INF);
    lufs_l_.setCurrentAndTargetValue(Global::METER_NEG_INF);
    lufs_r_.setCurrentAndTargetValue(Global::METER_NEG_INF);

    // Start the thread the band updater loop lives on.
    band_updater_.startPolling();

#ifdef TEST_FFT_ACCURACY
    juce::dsp::ProcessSpec fft_test_spec;

    fft_test_spec.sampleRate       = sample_rate;
    fft_test_spec.maximumBlockSize = samples_per_block;
    fft_test_spec.numChannels      = 1;

    fft_test_tone_.prepare(fft_test_spec);
    fft_test_tone_.initialise([](float f) { return std::sin(f); });
    fft_test_tone_gain_.prepare(fft_test_spec);

    updateFftTestTone();
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    const int num_inputs  = layouts.getMainInputChannels();
    const int num_outputs = layouts.getMainOutputChannels();

    return (num_inputs <= 4 && num_outputs <= 2);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::processBlock(juce::AudioBuffer< float >& buffer, juce::MidiBuffer& midi_messages)
{
    juce::ignoreUnused(midi_messages);

    juce::ScopedNoDenormals noDenormals;
    int                     total_num_input_channels  = getTotalNumInputChannels();
    int                     total_num_output_channels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = total_num_input_channels; i < total_num_output_channels; ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

#ifdef TEST_FFT_ACCURACY
    // Sine tone to test the FFT accuracy.
    buffer.clear();

    juce::dsp::AudioBlock< float >              fft_test_block(buffer);
    juce::dsp::ProcessContextReplacing< float > fft_test_context(fft_test_block);

    updateFftTestTone();
    fft_test_tone_.process(fft_test_context);
    fft_test_tone_gain_.process(fft_test_context);
#endif

    // Give the untouched input signal to the analysis filters.
    input_analysis_filter_.pushBufferForAnalysis(buffer);

    if (*apvts_.getRawParameterValue(GuiParams::getName(GuiParams::SHOW_FFT_SIDECHAIN))) {
        // Sidechain/Ambient FFT buffers (not affected by EQ).
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            fft_buffers_.at(Global::FFT::SIDECHAIN_LEFT)
                .pushNextSample(buffer.getSample(Global::Channels::SIDECHAIN_LEFT, i));
            fft_buffers_.at(Global::FFT::SIDECHAIN_RIGHT)
                .pushNextSample(buffer.getSample(Global::Channels::SIDECHAIN_RIGHT, i));
        }
    }

    if (*apvts_.getRawParameterValue(GuiParams::getName(GuiParams::SHOW_FFT_PRIMARY_PRE_EQ))) {
        // Primary/Playback FFT buffers (PRE EQ).
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            fft_buffers_.at(Global::FFT::PRIMARY_LEFT_PRE_EQ)
                .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_LEFT, i));
            fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_PRE_EQ)
                .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_RIGHT, i));
        }
    }

#ifdef TEST_FFT_ACCURACY
    // Clear the buffer so that the oscillator tone isn't processed by the filters
    // (and we don't have to listen to it).
    buffer.clear();
#endif

    // Update the filters from the new band values.
    updateFilterCoefficients();

    // Filter chains.
    juce::dsp::AudioBlock< float > audio_block(buffer);

    auto audio_block_left  = audio_block.getSingleChannelBlock(Global::Channels::PRIMARY_LEFT);
    auto audio_block_right = audio_block.getSingleChannelBlock(Global::Channels::PRIMARY_RIGHT);

    juce::dsp::ProcessContextReplacing< float > process_context_left(audio_block_left);
    juce::dsp::ProcessContextReplacing< float > process_context_right(audio_block_right);

    filter_chain_left_.process(process_context_left);
    filter_chain_right_.process(process_context_right);

    if (*apvts_.getRawParameterValue(GuiParams::getName(GuiParams::SHOW_FFT_PRIMARY_POST_EQ))) {
        // Primary/Playback FFT buffers (POST EQ).
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            fft_buffers_.at(Global::FFT::PRIMARY_LEFT_POST_EQ)
                .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_LEFT, i));
            fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_POST_EQ)
                .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_RIGHT, i));
        }
    }

    // Update the Peak, RMS, and LUFS.
    setPeak(peak_l_, buffer, Global::Channels::PRIMARY_LEFT);
    setPeak(peak_r_, buffer, Global::Channels::PRIMARY_RIGHT);

    setRms(rms_l_, buffer, Global::Channels::PRIMARY_LEFT);
    setRms(rms_r_, buffer, Global::Channels::PRIMARY_RIGHT);

    setLufs(lufs_l_, buffer, Global::Channels::PRIMARY_LEFT);
    setLufs(lufs_r_, buffer, Global::Channels::PRIMARY_RIGHT);
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::hasEditor() const
{
    return true;
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioProcessorEditor*
PluginProcessor::createEditor()
{
    return new PluginEditor(*this);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::getStateInformation(juce::MemoryBlock& dest_data)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused(dest_data);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::setStateInformation(const void* data, int size_in_bytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused(data, size_in_bytes);
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioProcessorValueTreeState&
PluginProcessor::getApvts()
{
    return apvts_;
}

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::BandDbValueArray&
PluginProcessor::getBandDbValues()
{
    return band_db_values_;
}

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::FftBuffers&
PluginProcessor::getFftBuffers()
{
    return fft_buffers_;
}

/*---------------------------------------------------------------------------
**
*/
Equalizer::MonoChain&
PluginProcessor::getFilterChain()
{
    // For the benefit of the analyser's filter response curve.
    // We're currently just returning a mono chain as left and right
    // are processed identically.
    return filter_chain_left_;
}

/*---------------------------------------------------------------------------
**
*/
float
PluginProcessor::getMeterValue(Global::Meters::METER_TYPE meter_type, Global::Channels::CHANNEL_ID channel_id) const
{
    if (channel_id != Global::Channels::PRIMARY_LEFT && channel_id != Global::Channels::PRIMARY_RIGHT) {
        return Global::METER_NEG_INF;
    }

    switch (meter_type) {
    case Global::Meters::PEAK_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? peak_l_.getCurrentValue() : peak_r_.getCurrentValue();

    case Global::Meters::RMS_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? rms_l_.getCurrentValue() : rms_r_.getCurrentValue();

    case Global::Meters::LUFS_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? lufs_l_.getCurrentValue() : lufs_r_.getCurrentValue();

    default:
        return Global::METER_NEG_INF;
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::updateFilterCoefficients()
{
    double sample_rate = getSampleRate();
    float  intensity   = apvts_.getParameter(GuiParams::getName(GuiParams::EQ_INTENSITY))->getValue();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID band_id     = static_cast< Equalizer::BAND_ID >(i);
        float              gain_factor = getNormalisedValue(getBandDb(band_id) * intensity);

        Equalizer::updateBandCoefficients(filter_chain_left_, band_id, gain_factor, sample_rate);
        Equalizer::updateBandCoefficients(filter_chain_right_, band_id, gain_factor, sample_rate);
    }
}

/*---------------------------------------------------------------------------
**
*/
float
PluginProcessor::getBandDb(Equalizer::BAND_ID band_id)
{
    return band_db_values_.at(band_id).getNextValue();
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::setPeak(SmoothedFloat& val, juce::AudioBuffer< float >& buffer, Global::Channels::CHANNEL_ID channel)
{
    int num_samples = buffer.getNumSamples();
    float new_value = juce::Decibels::gainToDecibels(buffer.getMagnitude(channel, 0, num_samples), Global::METER_NEG_INF);

    val.skip(num_samples);

    // new value >  current value: jump to it immediately.
    // new value <= current value: ramp to it gradually.
    new_value > val.getCurrentValue() ? val.setCurrentAndTargetValue(new_value) : val.setTargetValue(new_value);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::setRms(SmoothedFloat& val, juce::AudioBuffer< float >& buffer, Global::Channels::CHANNEL_ID channel)
{
    int num_samples = buffer.getNumSamples();
    float new_value = juce::Decibels::gainToDecibels(buffer.getRMSLevel(channel, 0, num_samples), Global::METER_NEG_INF);

    val.skip(num_samples);

    // new value >  current value: jump to it immediately.
    // new value <= current value: ramp to it gradually.
    new_value > val.getCurrentValue() ? val.setCurrentAndTargetValue(new_value) : val.setTargetValue(new_value);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::setLufs(SmoothedFloat& val, juce::AudioBuffer< float >& buffer, Global::Channels::CHANNEL_ID channel)
{
    juce::ignoreUnused(val, buffer, channel);
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
PluginProcessor::getNormalisedValue(float full_range_value)
{
    // The gain factor that needs to be supplied to the filters works on a >1 boost, <1 attenuate basis.
    // Map our -12 to +12 values to a 0 to 2 range (so 1 is the central "do nothing" point).
    return juce::jmap< float >(full_range_value, Global::MAX_DB_CUT, Global::MAX_DB_BOOST, 0.f, 2.f);
}

/*---------------------------------------------------------------------------
**
*/
/*static*/
juce::AudioProcessorValueTreeState::ParameterLayout
PluginProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout pl;

    juce::String intensity        = GuiParams::getName(GuiParams::EQ_INTENSITY);
    juce::String fft_primary_pre  = GuiParams::getName(GuiParams::SHOW_FFT_PRIMARY_PRE_EQ);
    juce::String fft_primary_post = GuiParams::getName(GuiParams::SHOW_FFT_PRIMARY_POST_EQ);
    juce::String fft_sidechain    = GuiParams::getName(GuiParams::SHOW_FFT_SIDECHAIN);

    pl.add(std::make_unique< juce::AudioParameterFloat >(juce::ParameterID(intensity, 1),
                                                         intensity,
                                                         juce::NormalisableRange< float >(0.f, 1.f, 0.01f, 1.f),
                                                         0.5f));

    pl.add(std::make_unique< juce::AudioParameterBool >(juce::ParameterID(fft_primary_pre, 1), fft_primary_pre, true));
    pl.add(std::make_unique< juce::AudioParameterBool >(juce::ParameterID(fft_primary_post, 1), fft_primary_post, false));
    pl.add(std::make_unique< juce::AudioParameterBool >(juce::ParameterID(fft_sidechain, 1), fft_sidechain, false));

#ifdef TEST_FFT_ACCURACY
    juce::String fft_test_hz = GuiParams::getName(GuiParams::FFT_ACCURACY_TEST_TONE_HZ);
    juce::String fft_test_db = GuiParams::getName(GuiParams::FFT_ACCURACY_TEST_TONE_DB);

    pl.add(std::make_unique< juce::AudioParameterFloat >(
        juce::ParameterID(fft_test_hz, 1),
        fft_test_hz,
        juce::NormalisableRange< float >(Global::MIN_HZ, Global::MAX_HZ, 1.f, 1.f),
        1000.f));

    pl.add(std::make_unique< juce::AudioParameterFloat >(
        juce::ParameterID(fft_test_db, 1),
        fft_test_db,
        juce::NormalisableRange< float >(Global::MAX_DB_CUT, Global::MAX_DB_BOOST, 1.f, 1.f),
        0.f));
#endif

    return pl;
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::updateFftTestTone()
{
#ifdef TEST_FFT_ACCURACY
    juce::RangedAudioParameter* test_tone_hz_param = apvts_.getParameter(
        GuiParams::getName(GuiParams::FFT_ACCURACY_TEST_TONE_HZ));

    juce::RangedAudioParameter* test_tone_db_param = apvts_.getParameter(
        GuiParams::getName(GuiParams::FFT_ACCURACY_TEST_TONE_DB));

    if (test_tone_hz_param != nullptr) {
        float frequency = juce::jmap< float >(test_tone_hz_param->getValue(), 0.f, 1.f, Global::MIN_HZ, Global::MAX_HZ);
        fft_test_tone_.setFrequency(frequency);
    }

    if (test_tone_db_param != nullptr) {
        float db = juce::jmap< float >(test_tone_db_param->getValue(), 0.f, 1.f, Global::MAX_DB_CUT, Global::MAX_DB_BOOST);
        fft_test_tone_gain_.setGainDecibels(db);
    }
#endif
}

/*---------------------------------------------------------------------------
** This creates new instances of the plugin.
*/
juce::AudioProcessor* JUCE_CALLTYPE
createPluginFilter()
{
    return new PluginProcessor();
}

/*---------------------------------------------------------------------------
** End of File
*/
