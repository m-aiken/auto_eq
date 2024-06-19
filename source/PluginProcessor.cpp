#include "PluginProcessor.h"
#include "PluginEditor.h"

/*static*/ const double PluginProcessor::SMOOTHED_VALUE_RAMP_TIME_SECONDS = 0.2;

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
        band.reset(sample_rate, SMOOTHED_VALUE_RAMP_TIME_SECONDS);
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
    peak_l_.reset(sample_rate, SMOOTHED_VALUE_RAMP_TIME_SECONDS);
    peak_r_.reset(sample_rate, SMOOTHED_VALUE_RAMP_TIME_SECONDS);
    rms_l_.reset(sample_rate, SMOOTHED_VALUE_RAMP_TIME_SECONDS);
    rms_r_.reset(sample_rate, SMOOTHED_VALUE_RAMP_TIME_SECONDS);
    lufs_l_.reset(sample_rate, SMOOTHED_VALUE_RAMP_TIME_SECONDS);
    lufs_r_.reset(sample_rate, SMOOTHED_VALUE_RAMP_TIME_SECONDS);

    peak_l_.setCurrentAndTargetValue(Global::NEG_INF);
    peak_r_.setCurrentAndTargetValue(Global::NEG_INF);
    rms_l_.setCurrentAndTargetValue(Global::NEG_INF);
    rms_r_.setCurrentAndTargetValue(Global::NEG_INF);
    lufs_l_.setCurrentAndTargetValue(Global::NEG_INF);
    lufs_r_.setCurrentAndTargetValue(Global::NEG_INF);

    // Start the thread the band updater loop lives on.
    band_updater_.startPolling();
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

    // Give the untouched input signal to the analysis filters.
    input_analysis_filter_.pushBufferForAnalysis(buffer);

    if (Global::PROCESS_FFT) {
        // Sidechain/Ambient FFT buffers (not affected by EQ).
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            fft_buffers_.at(Global::FFT::SIDECHAIN_LEFT)
                .pushNextSample(buffer.getSample(Global::Channels::SIDECHAIN_LEFT, i));
            fft_buffers_.at(Global::FFT::SIDECHAIN_RIGHT)
                .pushNextSample(buffer.getSample(Global::Channels::SIDECHAIN_RIGHT, i));
        }
    }

    if (Global::PROCESS_FFT) {
        // Primary/Playback FFT buffers (PRE EQ).
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            fft_buffers_.at(Global::FFT::PRIMARY_LEFT_PRE_EQ)
                .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_LEFT, i));
            fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_PRE_EQ)
                .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_RIGHT, i));
        }
    }

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

    if (Global::PROCESS_FFT) {
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
        return Global::NEG_INF;
    }

    switch (meter_type) {
    case Global::Meters::PEAK_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? peak_l_.getCurrentValue() : peak_r_.getCurrentValue();

    case Global::Meters::RMS_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? rms_l_.getCurrentValue() : rms_r_.getCurrentValue();

    case Global::Meters::LUFS_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? lufs_l_.getCurrentValue() : lufs_r_.getCurrentValue();

    default:
        return Global::NEG_INF;
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::updateFilterCoefficients()
{
    double sample_rate = getSampleRate();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID band_id = static_cast< Equalizer::BAND_ID >(i);
        float              gain    = getBandGain(band_id);

        Equalizer::updateBandCoefficients(filter_chain_left_, band_id, gain, sample_rate);
        Equalizer::updateBandCoefficients(filter_chain_right_, band_id, gain, sample_rate);
    }
}

/*---------------------------------------------------------------------------
**
*/
float
PluginProcessor::getBandGain(Equalizer::BAND_ID band_id)
{
    return juce::Decibels::decibelsToGain(band_db_values_.at(band_id).getNextValue());
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::setPeak(SmoothedFloat& val, juce::AudioBuffer< float >& buffer, Global::Channels::CHANNEL_ID channel)
{
    int   num_samples = buffer.getNumSamples();
    float new_value   = juce::Decibels::gainToDecibels(buffer.getMagnitude(channel, 0, num_samples), Global::NEG_INF);

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
    int   num_samples = buffer.getNumSamples();
    float new_value   = juce::Decibels::gainToDecibels(buffer.getRMSLevel(channel, 0, num_samples), Global::NEG_INF);

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
