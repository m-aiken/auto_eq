#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class PluginProcessor final : public juce::AudioProcessor
{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay(double sample_rate, int samples_per_block) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer< float >& buffer, juce::MidiBuffer& midi_messages) override;
    using AudioProcessor::processBlock;

    juce::AudioProcessorEditor* createEditor() override;
    bool                        hasEditor() const override;

    const juce::String getName() const override;

    bool   acceptsMidi() const override;
    bool   producesMidi() const override;
    bool   isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int                getNumPrograms() override;
    int                getCurrentProgram() override;
    void               setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void               changeProgramName(int index, const juce::String& new_name) override;

    void getStateInformation(juce::MemoryBlock& dest_data) override;
    void setStateInformation(const void* data, int size_in_bytes) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
