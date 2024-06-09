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
    , apvts_(*this, nullptr, "APVTS", getParameterLayout())
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
    // Pre-playback initialisation.

    juce::dsp::ProcessSpec process_spec;

    process_spec.sampleRate       = sample_rate;
    process_spec.maximumBlockSize = samples_per_block;
    process_spec.numChannels      = getTotalNumOutputChannels();

    // Input analysis filters.
    input_analysis_filter_l_.prepare(process_spec);
    input_analysis_filter_r_.prepare(process_spec);

    input_analysis_filter_l_.coefficients = juce::dsp::IIR::Coefficients< float >::makeAllPass(sample_rate,
                                                                                               (sample_rate * 0.5));
    input_analysis_filter_r_.coefficients = juce::dsp::IIR::Coefficients< float >::makeAllPass(sample_rate,
                                                                                               (sample_rate * 0.5));

    // FFT buffers.
    fft_buffers_.at(Global::FFT::PRIMARY_LEFT_PRE_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_PRE_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::PRIMARY_LEFT_POST_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_POST_EQ).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::SIDECHAIN_LEFT).prepare(sample_rate);
    fft_buffers_.at(Global::FFT::SIDECHAIN_RIGHT).prepare(sample_rate);

    // Filter chains.
    filter_chain_left_.prepare(process_spec);
    filter_chain_right_.prepare(process_spec);

    // EQ bands (filters).
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
    processInputForAnalysis(buffer);

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

    // Adjust the EQ band values based on the input analysis.
    updateBandValues();

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
juce::AudioProcessorValueTreeState&
PluginProcessor::getApvts()
{
    return apvts_;
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
FilterFactory::MonoChain&
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
PluginProcessor::getMeterValue(Global::METER_TYPE meter_type, Global::Channels::CHANNEL_ID channel_id) const
{
    if (channel_id != Global::Channels::PRIMARY_LEFT && channel_id != Global::Channels::PRIMARY_RIGHT) {
        return Global::NEG_INF;
    }

    switch (meter_type) {
    case Global::PEAK_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? peak_l_.getCurrentValue() : peak_r_.getCurrentValue();

    case Global::RMS_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? rms_l_.getCurrentValue() : rms_r_.getCurrentValue();

    case Global::LUFS_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? lufs_l_.getCurrentValue() : lufs_r_.getCurrentValue();

    default:
        return Global::NEG_INF;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::AudioProcessorValueTreeState::ParameterLayout
PluginProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameter_layout;

    // EQ bands.
    for (uint8 i = 0; i < FilterFactory::NUM_BANDS; ++i) {
        FilterFactory::addBandToParameterLayout(parameter_layout, static_cast< FilterFactory::BAND_ID >(i));
    }

    return parameter_layout;
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::processInputForAnalysis(juce::AudioBuffer< float >& buffer)
{
    juce::dsp::AudioBlock< float > analysis_block(buffer);

    auto analysis_block_l = analysis_block.getSingleChannelBlock(Global::Channels::PRIMARY_LEFT);
    auto analysis_block_r = analysis_block.getSingleChannelBlock(Global::Channels::PRIMARY_RIGHT);

    juce::dsp::ProcessContextReplacing< float > analysis_context_l(analysis_block_l);
    juce::dsp::ProcessContextReplacing< float > analysis_context_r(analysis_block_r);

    input_analysis_filter_l_.process(analysis_context_l);
    input_analysis_filter_r_.process(analysis_context_r);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::updateBandValues()
{
    double sample_rate = getSampleRate();

    for (uint8 i = 0; i < FilterFactory::NUM_BANDS; ++i) {
        FilterFactory::BAND_ID band_id = static_cast< FilterFactory::BAND_ID >(i);

        juce::AudioParameterFloat* param = getBandParameter(band_id);

        if (param == nullptr) {
            continue;
        }

        // Get the frequency for this band.
        float band_hz = FilterFactory::getBandHz(band_id);

        // Get the input magnitudes at that frequency.
        // We want the average of both channels (left and right);
        double input_mag_l   = input_analysis_filter_l_.coefficients->getMagnitudeForFrequency(band_hz, sample_rate);
        double input_mag_r   = input_analysis_filter_r_.coefficients->getMagnitudeForFrequency(band_hz, sample_rate);
        double input_mav_avg = (input_mag_l + input_mag_r) * 0.5;

        // Get the decibel value.
        float input_db = juce::Decibels::gainToDecibels(static_cast< float >(input_mav_avg), Global::NEG_INF);

        // Get the target decibel value for this band's frequency.
        float target_db = FilterFactory::getBandTargetDb(band_id);

        // Adjust the band's decibel value up/down to the target.
        param->setValueNotifyingHost(target_db - input_db);
    }
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioParameterFloat*
PluginProcessor::getBandParameter(FilterFactory::BAND_ID band_id)
{
    return dynamic_cast< juce::AudioParameterFloat* >(apvts_.getParameter(FilterFactory::getBandName(band_id)));
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::updateFilterCoefficients()
{
    double sample_rate = getSampleRate();

    for (uint8 i = 0; i < FilterFactory::NUM_BANDS; ++i) {
        FilterFactory::BAND_ID band_id = static_cast< FilterFactory::BAND_ID >(i);
        float                  gain    = getBandGain(band_id);

        FilterFactory::updateBandCoefficients(filter_chain_left_, band_id, gain, sample_rate);
        FilterFactory::updateBandCoefficients(filter_chain_right_, band_id, gain, sample_rate);
    }
}

/*---------------------------------------------------------------------------
**
*/
float
PluginProcessor::getBandGain(FilterFactory::BAND_ID band_id) const
{
    juce::String         param_id    = FilterFactory::getBandName(band_id);
    AudioParameterFloat* float_param = dynamic_cast< juce::AudioParameterFloat* >(apvts_.getParameter(param_id));

    return (float_param != nullptr) ? juce::Decibels::decibelsToGain(float_param->get()) : 0.f;
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
