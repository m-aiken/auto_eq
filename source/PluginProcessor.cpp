#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "dsp/EqParams.h"

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
    , peak_l_(0.f)
    , peak_r_(0.f)
    , rms_l_(0.f)
    , rms_r_(0.f)
    , lufs_l_(0.f)
    , lufs_r_(0.f)
{
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.low_cut_.freq_, EqParams::LOW_CUT_FREQ);
    assignParameter< juce::AudioParameterChoice* >(filter_bands_.low_cut_.slope_, EqParams::LOW_CUT_SLOPE);
    assignParameter< juce::AudioParameterBool* >(filter_bands_.low_cut_.enabled_, EqParams::LOW_CUT_ENABLED);

    assignParameter< juce::AudioParameterFloat* >(filter_bands_.low_shelf_.freq_, EqParams::LOW_SHELF_FREQ);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.low_shelf_.gain_, EqParams::LOW_SHELF_GAIN);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.low_shelf_.q_, EqParams::LOW_SHELF_Q);

    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_1_.freq_, EqParams::PEAK_1_FREQ);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_2_.freq_, EqParams::PEAK_2_FREQ);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_3_.freq_, EqParams::PEAK_3_FREQ);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_4_.freq_, EqParams::PEAK_4_FREQ);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_5_.freq_, EqParams::PEAK_5_FREQ);

    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_1_.gain_, EqParams::PEAK_1_GAIN);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_2_.gain_, EqParams::PEAK_2_GAIN);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_3_.gain_, EqParams::PEAK_3_GAIN);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_4_.gain_, EqParams::PEAK_4_GAIN);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_5_.gain_, EqParams::PEAK_5_GAIN);

    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_1_.q_, EqParams::PEAK_1_Q);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_2_.q_, EqParams::PEAK_2_Q);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_3_.q_, EqParams::PEAK_3_Q);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_4_.q_, EqParams::PEAK_4_Q);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.peak_5_.q_, EqParams::PEAK_5_Q);

    assignParameter< juce::AudioParameterFloat* >(filter_bands_.high_shelf_.freq_, EqParams::HIGH_SHELF_FREQ);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.high_shelf_.gain_, EqParams::HIGH_SHELF_GAIN);
    assignParameter< juce::AudioParameterFloat* >(filter_bands_.high_shelf_.q_, EqParams::HIGH_SHELF_Q);

    assignParameter< juce::AudioParameterFloat* >(filter_bands_.high_cut_.freq_, EqParams::HIGH_CUT_FREQ);
    assignParameter< juce::AudioParameterChoice* >(filter_bands_.high_cut_.slope_, EqParams::HIGH_CUT_SLOPE);
    assignParameter< juce::AudioParameterBool* >(filter_bands_.high_cut_.enabled_, EqParams::HIGH_CUT_ENABLED);
}

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::~PluginProcessor()
{
    filter_bands_.low_cut_.freq_    = nullptr;
    filter_bands_.low_cut_.slope_   = nullptr;
    filter_bands_.low_cut_.enabled_ = nullptr;

    filter_bands_.low_shelf_.freq_ = nullptr;
    filter_bands_.low_shelf_.gain_ = nullptr;
    filter_bands_.low_shelf_.q_    = nullptr;

    filter_bands_.peak_1_.freq_ = nullptr;
    filter_bands_.peak_1_.gain_ = nullptr;
    filter_bands_.peak_1_.q_    = nullptr;

    filter_bands_.peak_2_.freq_ = nullptr;
    filter_bands_.peak_2_.gain_ = nullptr;
    filter_bands_.peak_2_.q_    = nullptr;

    filter_bands_.peak_3_.freq_ = nullptr;
    filter_bands_.peak_3_.gain_ = nullptr;
    filter_bands_.peak_3_.q_    = nullptr;

    filter_bands_.peak_4_.freq_ = nullptr;
    filter_bands_.peak_4_.gain_ = nullptr;
    filter_bands_.peak_4_.q_    = nullptr;

    filter_bands_.peak_5_.freq_ = nullptr;
    filter_bands_.peak_5_.gain_ = nullptr;
    filter_bands_.peak_5_.q_    = nullptr;

    filter_bands_.high_shelf_.freq_ = nullptr;
    filter_bands_.high_shelf_.gain_ = nullptr;
    filter_bands_.high_shelf_.q_    = nullptr;

    filter_bands_.high_cut_.freq_    = nullptr;
    filter_bands_.high_cut_.slope_   = nullptr;
    filter_bands_.high_cut_.enabled_ = nullptr;
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
    filter_chain_spec.numChannels      = getTotalNumOutputChannels();

    filter_chain_left_.prepare(filter_chain_spec);
    filter_chain_right_.prepare(filter_chain_spec);

    // EQ bands (filters).
    updateFilterCoefficients();
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

    // Sidechain/Ambient FFT buffers (not affected by EQ).
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        fft_buffers_.at(Global::FFT::SIDECHAIN_LEFT).pushNextSample(buffer.getSample(Global::Channels::SIDECHAIN_LEFT, i));
        fft_buffers_.at(Global::FFT::SIDECHAIN_RIGHT).pushNextSample(buffer.getSample(Global::Channels::SIDECHAIN_RIGHT, i));
    }

    // Primary/Playback FFT buffers (PRE EQ).
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        fft_buffers_.at(Global::FFT::PRIMARY_LEFT_PRE_EQ)
            .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_LEFT, i));

        fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_PRE_EQ)
            .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_RIGHT, i));
    }

    // EQ bands (filters).
    updateFilterCoefficients();

    // Filter chains.
    juce::dsp::AudioBlock< float > audio_block(buffer);

    auto audio_block_left  = audio_block.getSingleChannelBlock(Global::Channels::PRIMARY_LEFT);
    auto audio_block_right = audio_block.getSingleChannelBlock(Global::Channels::PRIMARY_RIGHT);

    juce::dsp::ProcessContextReplacing< float > process_context_left(audio_block_left);
    juce::dsp::ProcessContextReplacing< float > process_context_right(audio_block_right);

    filter_chain_left_.process(process_context_left);
    filter_chain_right_.process(process_context_right);

    // Primary/Playback FFT buffers (POST EQ).
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        fft_buffers_.at(Global::FFT::PRIMARY_LEFT_POST_EQ)
            .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_LEFT, i));

        fft_buffers_.at(Global::FFT::PRIMARY_RIGHT_POST_EQ)
            .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_RIGHT, i));
    }

    // Get the Peak, RMS, and LUFS.
    peak_l_ = juce::Decibels::gainToDecibels(buffer.getMagnitude(Global::Channels::PRIMARY_LEFT, 0, buffer.getNumSamples()),
                                             Global::NEG_INF);

    peak_r_ =
        juce::Decibels::gainToDecibels(buffer.getMagnitude(Global::Channels::PRIMARY_RIGHT, 0, buffer.getNumSamples()),
                                       Global::NEG_INF);

    rms_l_ = juce::Decibels::gainToDecibels(buffer.getRMSLevel(Global::Channels::PRIMARY_LEFT, 0, buffer.getNumSamples()),
                                            Global::NEG_INF);

    rms_r_ = juce::Decibels::gainToDecibels(buffer.getRMSLevel(Global::Channels::PRIMARY_LEFT, 0, buffer.getNumSamples()),
                                            Global::NEG_INF);
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
FilterFactory::BandSet&
PluginProcessor::getFilterBands()
{
    return filter_bands_;
}

/*---------------------------------------------------------------------------
**
*/
float
PluginProcessor::getMeterValue(Global::METER_TYPE meter_type, Global::Channels::CHANNEL_ID channel_id) const
{
    if (channel_id != Global::Channels::PRIMARY_LEFT && channel_id != Global::Channels::PRIMARY_RIGHT) {
        return 0.f;
    }

    switch (meter_type) {
    case Global::PEAK_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? peak_l_ : peak_r_;

    case Global::RMS_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? rms_l_ : rms_r_;

    case Global::LUFS_METER:
        return (channel_id == Global::Channels::PRIMARY_LEFT) ? lufs_l_ : lufs_r_;

    default:
        return 0.f;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::AudioProcessorValueTreeState::ParameterLayout
PluginProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameter_layout;

    //
    // EQ.
    //

    // Low Cut.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::LOW_CUT_FREQ, Global::MIN_HZ, 500.f);
    EqParams::addCutChoiceParamToLayout(parameter_layout, EqParams::LOW_CUT_SLOPE);
    EqParams::addEnabledParamToLayout(parameter_layout, EqParams::LOW_CUT_ENABLED);

    // Low Shelf.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::LOW_SHELF_FREQ, Global::MIN_HZ, 500.f);
    EqParams::addGainParamToLayout(parameter_layout, EqParams::LOW_SHELF_GAIN);
    EqParams::addQualParamToLayout(parameter_layout, EqParams::LOW_SHELF_Q);

    // Peak 1.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::PEAK_1_FREQ);
    EqParams::addGainParamToLayout(parameter_layout, EqParams::PEAK_1_GAIN);
    EqParams::addQualParamToLayout(parameter_layout, EqParams::PEAK_1_Q);

    // Peak 2.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::PEAK_2_FREQ);
    EqParams::addGainParamToLayout(parameter_layout, EqParams::PEAK_2_GAIN);
    EqParams::addQualParamToLayout(parameter_layout, EqParams::PEAK_2_Q);

    // Peak 3.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::PEAK_3_FREQ);
    EqParams::addGainParamToLayout(parameter_layout, EqParams::PEAK_3_GAIN);
    EqParams::addQualParamToLayout(parameter_layout, EqParams::PEAK_3_Q);

    // Peak 4.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::PEAK_4_FREQ);
    EqParams::addGainParamToLayout(parameter_layout, EqParams::PEAK_4_GAIN);
    EqParams::addQualParamToLayout(parameter_layout, EqParams::PEAK_4_Q);

    // Peak 5.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::PEAK_5_FREQ);
    EqParams::addGainParamToLayout(parameter_layout, EqParams::PEAK_5_GAIN);
    EqParams::addQualParamToLayout(parameter_layout, EqParams::PEAK_5_Q);

    // High Shelf.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::HIGH_SHELF_FREQ, 1000.f, Global::MAX_HZ);
    EqParams::addGainParamToLayout(parameter_layout, EqParams::HIGH_SHELF_GAIN);
    EqParams::addQualParamToLayout(parameter_layout, EqParams::HIGH_SHELF_Q);

    // High Cut.
    EqParams::addFreqParamToLayout(parameter_layout, EqParams::HIGH_CUT_FREQ, 1000.f, Global::MAX_HZ);
    EqParams::addCutChoiceParamToLayout(parameter_layout, EqParams::HIGH_CUT_SLOPE);
    EqParams::addEnabledParamToLayout(parameter_layout, EqParams::HIGH_CUT_ENABLED);

    return parameter_layout;
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::updateFilterCoefficients()
{
    double sample_rate = getSampleRate();

    if (filter_bands_.low_cut_.enabled_ != nullptr && filter_bands_.low_cut_.enabled_->get()) {
        FilterFactory::updateLowCut(filter_chain_left_, filter_bands_.low_cut_, sample_rate);
        FilterFactory::updateLowCut(filter_chain_right_, filter_bands_.low_cut_, sample_rate);
    }

    if (filter_bands_.high_cut_.enabled_ != nullptr && filter_bands_.high_cut_.enabled_->get()) {
        FilterFactory::updateHighCut(filter_chain_left_, filter_bands_.high_cut_, sample_rate);
        FilterFactory::updateHighCut(filter_chain_right_, filter_bands_.high_cut_, sample_rate);
    }

    FilterFactory::updateLowShelf(filter_chain_left_, filter_bands_.low_shelf_, sample_rate);
    FilterFactory::updateLowShelf(filter_chain_right_, filter_bands_.low_shelf_, sample_rate);

    FilterFactory::updateHighShelf(filter_chain_left_, filter_bands_.high_shelf_, sample_rate);
    FilterFactory::updateHighShelf(filter_chain_right_, filter_bands_.high_shelf_, sample_rate);

    FilterFactory::updatePeak(filter_chain_left_, FilterFactory::PEAK_1, filter_bands_.peak_1_, sample_rate);
    FilterFactory::updatePeak(filter_chain_right_, FilterFactory::PEAK_1, filter_bands_.peak_1_, sample_rate);

    FilterFactory::updatePeak(filter_chain_left_, FilterFactory::PEAK_2, filter_bands_.peak_2_, sample_rate);
    FilterFactory::updatePeak(filter_chain_right_, FilterFactory::PEAK_2, filter_bands_.peak_2_, sample_rate);

    FilterFactory::updatePeak(filter_chain_left_, FilterFactory::PEAK_3, filter_bands_.peak_3_, sample_rate);
    FilterFactory::updatePeak(filter_chain_right_, FilterFactory::PEAK_3, filter_bands_.peak_3_, sample_rate);

    FilterFactory::updatePeak(filter_chain_left_, FilterFactory::PEAK_4, filter_bands_.peak_4_, sample_rate);
    FilterFactory::updatePeak(filter_chain_right_, FilterFactory::PEAK_4, filter_bands_.peak_4_, sample_rate);

    FilterFactory::updatePeak(filter_chain_left_, FilterFactory::PEAK_5, filter_bands_.peak_5_, sample_rate);
    FilterFactory::updatePeak(filter_chain_right_, FilterFactory::PEAK_5, filter_bands_.peak_5_, sample_rate);
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
