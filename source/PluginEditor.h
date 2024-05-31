#pragma once

#include "PluginProcessor.h"
#include "gui/analyser/PrimaryAnalyser.h"
#include "gui/analyser/SidechainAnalyser.h"

class PluginEditor final : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor(PluginProcessor& p);
    ~PluginEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processor_ref_;

    juce::ToggleButton theme_button_;
    PrimaryAnalyser    primary_analyser_;
    SidechainAnalyser  sidechain_analyser_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
