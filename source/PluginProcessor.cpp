#include "GlobalConstants.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

/*static*/ const double PluginProcessor::METER_DB_RAMP_TIME_SECONDS = 0.2;

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , apvts_(*this, nullptr, "APVTS", getParameterLayout())
    , preset_manager_(apvts_)
    , input_analysis_filter_()
    , band_updater_(input_analysis_filter_)
    , band_parameter_updater_(apvts_, band_updater_)
    , unity_gain_calculator_(apvts_.getParameter(GuiParams::getName(GuiParams::MASTER_GAIN)))
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
    band_updater_.prepare(sample_rate);

    // Input analysis filter.
    juce::dsp::ProcessSpec analysis_spec;

    analysis_spec.sampleRate       = sample_rate;
    analysis_spec.maximumBlockSize = static_cast< juce::uint32 >(samples_per_block);
    analysis_spec.numChannels      = static_cast< juce::uint32 >(getTotalNumInputChannels());

    input_analysis_filter_.prepare(analysis_spec);

    // FFT buffers.
    fft_buffers_.at(Global::FFT::LEFT_POST_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::RIGHT_POST_EQ).prepare(sample_rate);

    // Filter chains.
    juce::dsp::ProcessSpec filter_chain_spec;

    filter_chain_spec.sampleRate       = sample_rate;
    filter_chain_spec.maximumBlockSize = static_cast< juce::uint32 >(samples_per_block);
    filter_chain_spec.numChannels      = 1;

    filter_chain_left_.prepare(filter_chain_spec);
    filter_chain_right_.prepare(filter_chain_spec);

    // Band pass filters.
    updateFilterCoefficients();

    // Meter values.
    for (auto& meter_val : meter_values_) {
        meter_val.reset(sample_rate, METER_DB_RAMP_TIME_SECONDS);
        meter_val.setCurrentAndTargetValue(Global::METER_NEG_INF);
    }

    // Initialise the empty buffer.
    empty_buffer_.setSize(Global::Channels::NUM_INPUTS, samples_per_block);
    empty_buffer_.clear();

    // Unity gain.
    unity_gain_calculator_.prepare(sample_rate, static_cast< juce::uint32 >(samples_per_block));

    // LUFS processing.
    lufs_module_.reset();

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
    // Some plugin hosts will only support mono or stereo output bus layouts.
    bool mono_out   = layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono();
    bool stereo_out = layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();

    // We want the input and output layouts to match (i.e. mono in --> mono out or stereo in --> stereo out).
    bool in_matches_out = layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();

    return (mono_out || stereo_out) && in_matches_out;
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

    if (!booleanParameterEnabled(GuiParams::POWER)) {
        // The plugin is being bypassed.
        // The threads responsible for the FFT, input analysis and EQ will already have been stopped.
        // Clear out the meter values.
        const int samples_to_skip = buffer.getNumSamples();

        for (auto& meter_val : meter_values_) {
            meter_val.skip(samples_to_skip);
            meter_val.setTargetValue(Global::METER_NEG_INF);  //! Ramp to the new value.
        }

        // Don't do any processing on the real buffer.
        return;
    }

    // Apply any input trim, then update the input gain meter value.
    applyInputTrim(buffer);
    updateMeterValue(Global::Meters::INPUT_GAIN, buffer);

    if (booleanParameterEnabled(GuiParams::UNITY_GAIN_ENABLED)) {
        unity_gain_calculator_.pushForAnalysis(buffer, UnityGainCalculator::PRE_PROCESSED_FIFO);
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
    if (input_analysis_filter_.isThreadRunning()) {
        input_analysis_filter_.pushBufferForAnalysis(buffer);
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

    auto audio_block_left  = audio_block.getSingleChannelBlock(Global::Channels::INPUT_LEFT);
    auto audio_block_right = audio_block.getSingleChannelBlock(Global::Channels::INPUT_RIGHT);

    juce::dsp::ProcessContextReplacing< float > process_context_left(audio_block_left);
    juce::dsp::ProcessContextReplacing< float > process_context_right(audio_block_right);

    filter_chain_left_.process(process_context_left);
    filter_chain_right_.process(process_context_right);

    if (!booleanParameterEnabled(GuiParams::POWER_SAVING)) {
        // FFT buffers (POST EQ).
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            fft_buffers_.at(Global::FFT::LEFT_POST_EQ).pushNextSample(buffer.getSample(Global::Channels::INPUT_LEFT, i));
            fft_buffers_.at(Global::FFT::RIGHT_POST_EQ).pushNextSample(buffer.getSample(Global::Channels::INPUT_RIGHT, i));
        }
    }

    if (booleanParameterEnabled(GuiParams::UNITY_GAIN_ENABLED)) {
        unity_gain_calculator_.pushForAnalysis(buffer, UnityGainCalculator::POST_PROCESSED_FIFO);
    }

    // Master gain.
    applyMasterGain(buffer);

    // LUFS.
    lufs_module_.processBlock(buffer);

    // Output meters.
    updateMeterValue(Global::Meters::OUTPUT_PEAK, buffer);
    updateMeterValue(Global::Meters::OUTPUT_RMS, buffer);
    updateMeterValue(Global::Meters::MOMENTARY_LOUDNESS, buffer);
    updateMeterValue(Global::Meters::SHORT_TERM_LOUDNESS, buffer);
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
PresetManager&
PluginProcessor::getPresetManager()
{
    return preset_manager_;
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::loadPreset(const int preset_index)
{
    const juce::ValueTree& preset = preset_manager_.getPreset(preset_index);

    if (!PresetManager::isValidPreset(preset)) {
        return false;
    }

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        const auto                  band_id      = static_cast< Equalizer::BAND_ID >(i);
        const juce::String          parameter_id = Equalizer::getBandName(band_id);
        juce::RangedAudioParameter* apvts_param  = apvts_.getParameter(parameter_id);

        if (apvts_param == nullptr) {
            continue;
        }

        const double band_gain = PresetManager::getPresetBandGain(preset, static_cast< Equalizer::BAND_ID >(i));
        const float  db_value  = apvts_param->convertTo0to1(band_gain);

        apvts_param->setValue(db_value);
    }

    updateFilterCoefficients();

    preset_manager_.setCurrentlyLoadedPresetName(preset_manager_.getPresetName(preset));

    return true;
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
PluginProcessor::getMeterValue(const Global::Meters::METER_TYPE meter_type) const
{
    return meter_values_.at(meter_type).getCurrentValue();
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::startInputAnalysis()
{
    if (input_analysis_filter_.isPrepared() && band_updater_.isPrepared()) {
        input_analysis_filter_.startThread();

        // The user may have manually changed the band values since the last analysis and subsequent auto-EQ.
        // Align the band updater's band values array with the values in the tree state.
        band_updater_.syncroniseWithTreeState(apvts_);
        band_updater_.startThread();

        band_parameter_updater_.startThread();
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::stopInputAnalysis()
{
    band_parameter_updater_.stopThread(BandParameterUpdater::UPDATE_FREQUENCY_MS);
    band_updater_.stopThread(BandUpdater::UPDATE_FREQUENCY_MS);
    input_analysis_filter_.stopThread(InputAnalysisFilter::ANALYSIS_FREQUENCY_MS);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::startUnityGainCalculation()
{
    if (unity_gain_calculator_.isPrepared()) {
        unity_gain_calculator_.startThread();
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::stopUnityGainCalculation()
{
    unity_gain_calculator_.stopThread(UnityGainCalculator::CALCULATION_FREQUENCY_MS);
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::booleanParameterEnabled(GuiParams::PARAM_ID param_id) const
{
    juce::RangedAudioParameter* param = apvts_.getParameter(GuiParams::getName(param_id));

    return (param != nullptr) && static_cast< bool >(param->getValue());
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::updateFilterCoefficients()
{
    juce::RangedAudioParameter* intensity_param = apvts_.getParameter(GuiParams::getName(GuiParams::EQ_INTENSITY));

    if (intensity_param == nullptr) {
        return;
    }

    double sample_rate = getSampleRate();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID          band_id      = static_cast< Equalizer::BAND_ID >(i);
        juce::String                parameter_id = Equalizer::getBandName(band_id);
        juce::RangedAudioParameter* apvts_param  = apvts_.getParameter(parameter_id);

        if (apvts_param == nullptr) {
            continue;
        }

        float db_value    = apvts_param->convertFrom0to1(apvts_param->getValue());
        float gain_factor = getNormalisedValue(db_value * intensity_param->getValue());

        Equalizer::updateBandCoefficients(filter_chain_left_, band_id, gain_factor, sample_rate);
        Equalizer::updateBandCoefficients(filter_chain_right_, band_id, gain_factor, sample_rate);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::updateMeterValue(Global::Meters::METER_TYPE meter, const juce::AudioBuffer< float >& buffer)
{
    const int num_samples = buffer.getNumSamples();
    float     new_value   = Global::METER_NEG_INF;

    switch (meter) {
    case Global::Meters::INPUT_GAIN:
    case Global::Meters::OUTPUT_PEAK:
        new_value = juce::Decibels::gainToDecibels(buffer.getMagnitude(0, num_samples), Global::METER_NEG_INF);
        break;

    case Global::Meters::OUTPUT_RMS:
    {
        const float rms_l_gain = buffer.getRMSLevel(Global::Channels::INPUT_LEFT, 0, num_samples);
        const float rms_l_db   = juce::Decibels::gainToDecibels(rms_l_gain, Global::METER_NEG_INF);
        const float rms_r_gain = buffer.getRMSLevel(Global::Channels::INPUT_RIGHT, 0, num_samples);
        const float rms_r_db   = juce::Decibels::gainToDecibels(rms_r_gain, Global::METER_NEG_INF);

        new_value = (rms_l_db + rms_r_db) / 2.f;

        break;
    }

    case Global::Meters::MOMENTARY_LOUDNESS:
        new_value = lufs_module_.getMomentaryLoudness();
        break;

    case Global::Meters::SHORT_TERM_LOUDNESS:
        new_value = lufs_module_.getShortTermLoudness();
        break;

    default:
        break;
    }

    SmoothedFloat& current_meter_val = meter_values_.at(meter);

    current_meter_val.skip(num_samples);

    // new value >  current value: jump to it immediately.
    // new value <= current value: ramp to it gradually.
    new_value > current_meter_val.getCurrentValue() ? current_meter_val.setCurrentAndTargetValue(new_value) :
                                                      current_meter_val.setTargetValue(new_value);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::applyInputTrim(juce::AudioBuffer< float >& buffer) const
{
    const juce::RangedAudioParameter* input_trim_param = apvts_.getParameter(GuiParams::getName(GuiParams::INPUT_TRIM));

    if (input_trim_param == nullptr) {
        return;
    }

    const float raw_val = input_trim_param->getValue();
    const float db      = input_trim_param->convertFrom0to1(raw_val);
    const float gain    = juce::Decibels::decibelsToGain(db, Global::NEG_INF);

    buffer.applyGain(gain);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::applyMasterGain(juce::AudioBuffer< float >& buffer)
{
    const juce::RangedAudioParameter* master_gain_param = apvts_.getParameter(GuiParams::getName(GuiParams::MASTER_GAIN));

    if (master_gain_param == nullptr) {
        return;
    }

    const bool  unity_gain = booleanParameterEnabled(GuiParams::UNITY_GAIN_ENABLED);
    const float raw_val    = unity_gain ? unity_gain_calculator_.getGainAdjustment() : master_gain_param->getValue();
    const float db         = master_gain_param->convertFrom0to1(raw_val);
    const float gain       = juce::Decibels::decibelsToGain(db, Global::NEG_INF);

    buffer.applyGain(gain);
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

    juce::String power_param_id        = GuiParams::getName(GuiParams::POWER);
    juce::String analysis_param_id     = GuiParams::getName(GuiParams::ANALYSE_INPUT);
    juce::String power_saving_param_id = GuiParams::getName(GuiParams::POWER_SAVING);
    juce::String input_trim_param_id   = GuiParams::getName(GuiParams::INPUT_TRIM);
    juce::String eq_intensity_param_id = GuiParams::getName(GuiParams::EQ_INTENSITY);
    juce::String master_gain_param_id  = GuiParams::getName(GuiParams::MASTER_GAIN);
    juce::String unity_gain_param_id   = GuiParams::getName(GuiParams::UNITY_GAIN_ENABLED);

    juce::NormalisableRange< float > band_range(Global::MAX_DB_CUT, Global::MAX_DB_BOOST, 0.01f, 1.f);

    juce::NormalisableRange< float > input_trim_range(GuiParams::INPUT_TRIM_MIN,
                                                      GuiParams::INPUT_TRIM_MAX,
                                                      GuiParams::INPUT_TRIM_INTERVAL,
                                                      1.f);

    juce::NormalisableRange< float > master_gain_range(GuiParams::MASTER_GAIN_MIN,
                                                       GuiParams::MASTER_GAIN_MAX,
                                                       GuiParams::MASTER_GAIN_INTERVAL,
                                                       1.f);

    pl.add(std::make_unique< juce::AudioParameterBool >(juce::ParameterID(power_param_id, 1),
                                                        power_param_id,
                                                        GuiParams::INITIAL_POWER_STATE));

    pl.add(std::make_unique< juce::AudioParameterBool >(juce::ParameterID(analysis_param_id, 1),
                                                        analysis_param_id,
                                                        GuiParams::INITIAL_ANALYSIS_STATE));

    pl.add(std::make_unique< juce::AudioParameterBool >(juce::ParameterID(power_saving_param_id, 1),
                                                        power_saving_param_id,
                                                        GuiParams::INITIAL_POWER_SAVING_STATE));

    pl.add(std::make_unique< juce::AudioParameterFloat >(juce::ParameterID(input_trim_param_id, 1),
                                                         input_trim_param_id,
                                                         input_trim_range,
                                                         GuiParams::INITIAL_INPUT_TRIM));

    pl.add(std::make_unique< juce::AudioParameterInt >(juce::ParameterID(eq_intensity_param_id, 1),
                                                       eq_intensity_param_id,
                                                       0,
                                                       100,
                                                       100));

    pl.add(std::make_unique< juce::AudioParameterFloat >(juce::ParameterID(master_gain_param_id, 1),
                                                         master_gain_param_id,
                                                         master_gain_range,
                                                         GuiParams::INITIAL_MASTER_GAIN));

    pl.add(std::make_unique< juce::AudioParameterBool >(juce::ParameterID(unity_gain_param_id, 1),
                                                        unity_gain_param_id,
                                                        GuiParams::INITIAL_UNITY_GAIN_STATE));

    for (size_t i = 0; i < Equalizer::NUM_BANDS; ++i) {
        juce::String band_str = Equalizer::getBandName(static_cast< Equalizer::BAND_ID >(i));

        pl.add(std::make_unique< juce::AudioParameterFloat >(juce::ParameterID(band_str, 1), band_str, band_range, 0.f));
    }

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
