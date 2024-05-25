#include "PluginProcessor.h"
#include "PluginEditor.h"

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::quadraphonic(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
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

    fft_buffer_playback_source_l_.prepare(sample_rate);
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
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
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

    const float* channel_1_data = buffer.getReadPointer(0);

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        fft_buffer_playback_source_l_.pushNextSample(channel_1_data[i]);
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
MonoFftBuffer&
PluginProcessor::getFftBufferPlaybackSourceL()
{
    return fft_buffer_playback_source_l_;
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
