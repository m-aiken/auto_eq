#include "PluginProcessor.h"
#include "PluginEditor.h"

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::PluginProcessor()
    : AudioProcessor(
        BusesProperties()
            .withInput(Global::Channels::getChannelName(Global::Channels::PRIMARY_LEFT), juce::AudioChannelSet::mono(), true)
            .withInput(Global::Channels::getChannelName(Global::Channels::PRIMARY_RIGHT), juce::AudioChannelSet::mono(), true)
            .withInput(Global::Channels::getChannelName(Global::Channels::SIDECHAIN_LEFT),
                       juce::AudioChannelSet::mono(),
                       true)
            .withInput(Global::Channels::getChannelName(Global::Channels::SIDECHAIN_RIGHT),
                       juce::AudioChannelSet::mono(),
                       true)
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
    juce::ignoreUnused(samples_per_block);

    fft_buffers_.at(Global::Channels::PRIMARY_LEFT).prepare(sample_rate);
    fft_buffers_.at(Global::Channels::PRIMARY_RIGHT).prepare(sample_rate);
    fft_buffers_.at(Global::Channels::SIDECHAIN_LEFT).prepare(sample_rate);
    fft_buffers_.at(Global::Channels::SIDECHAIN_RIGHT).prepare(sample_rate);
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

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        fft_buffers_.at(Global::Channels::PRIMARY_LEFT).pushNextSample(buffer.getSample(Global::Channels::PRIMARY_LEFT, i));

        fft_buffers_.at(Global::Channels::PRIMARY_RIGHT)
            .pushNextSample(buffer.getSample(Global::Channels::PRIMARY_RIGHT, i));

        fft_buffers_.at(Global::Channels::SIDECHAIN_LEFT)
            .pushNextSample(buffer.getSample(Global::Channels::SIDECHAIN_LEFT, i));

        fft_buffers_.at(Global::Channels::SIDECHAIN_RIGHT)
            .pushNextSample(buffer.getSample(Global::Channels::SIDECHAIN_RIGHT, i));
    }
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
PluginProcessor::FftBuffers&
PluginProcessor::getFftBuffers()
{
    return fft_buffers_;
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
    Global::EQ::addCutFreqParamToLayout(parameter_layout, Global::EQ::LOW_CUT_FREQ, Global::MIN_HZ);
    Global::EQ::addCutChoiceParamToLayout(parameter_layout, Global::EQ::LOW_CUT_SLOPE);
    Global::EQ::addEnabledParamToLayout(parameter_layout, Global::EQ::LOW_CUT_ENABLED);

    // Peak 1.
    Global::EQ::addPeakFreqParamToLayout(parameter_layout, Global::EQ::PEAK_1_FREQ);
    Global::EQ::addPeakGainParamToLayout(parameter_layout, Global::EQ::PEAK_1_GAIN);
    Global::EQ::addPeakQualParamToLayout(parameter_layout, Global::EQ::PEAK_1_Q);

    // Peak 2.
    Global::EQ::addPeakFreqParamToLayout(parameter_layout, Global::EQ::PEAK_2_FREQ);
    Global::EQ::addPeakGainParamToLayout(parameter_layout, Global::EQ::PEAK_2_GAIN);
    Global::EQ::addPeakQualParamToLayout(parameter_layout, Global::EQ::PEAK_2_Q);

    // Peak 3.
    Global::EQ::addPeakFreqParamToLayout(parameter_layout, Global::EQ::PEAK_3_FREQ);
    Global::EQ::addPeakGainParamToLayout(parameter_layout, Global::EQ::PEAK_3_GAIN);
    Global::EQ::addPeakQualParamToLayout(parameter_layout, Global::EQ::PEAK_3_Q);

    // Peak 4.
    Global::EQ::addPeakFreqParamToLayout(parameter_layout, Global::EQ::PEAK_4_FREQ);
    Global::EQ::addPeakGainParamToLayout(parameter_layout, Global::EQ::PEAK_4_GAIN);
    Global::EQ::addPeakQualParamToLayout(parameter_layout, Global::EQ::PEAK_4_Q);

    // Peak 5.
    Global::EQ::addPeakFreqParamToLayout(parameter_layout, Global::EQ::PEAK_5_FREQ);
    Global::EQ::addPeakGainParamToLayout(parameter_layout, Global::EQ::PEAK_5_GAIN);
    Global::EQ::addPeakQualParamToLayout(parameter_layout, Global::EQ::PEAK_5_Q);

    // Peak 6.
    Global::EQ::addPeakFreqParamToLayout(parameter_layout, Global::EQ::PEAK_6_FREQ);
    Global::EQ::addPeakGainParamToLayout(parameter_layout, Global::EQ::PEAK_6_GAIN);
    Global::EQ::addPeakQualParamToLayout(parameter_layout, Global::EQ::PEAK_6_Q);

    // High Cut.
    Global::EQ::addCutFreqParamToLayout(parameter_layout, Global::EQ::HIGH_CUT_FREQ, Global::MAX_HZ);
    Global::EQ::addCutChoiceParamToLayout(parameter_layout, Global::EQ::HIGH_CUT_SLOPE);
    Global::EQ::addEnabledParamToLayout(parameter_layout, Global::EQ::HIGH_CUT_ENABLED);

    return parameter_layout;
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
