#pragma once

#include "PluginProcessor.h"
#include "gui/ThemeButton.h"
#include "gui/analyser/Analyser.h"

class PluginEditor final
    : public juce::AudioProcessorEditor
    , public juce::Button::Listener
{
public:
    explicit PluginEditor(PluginProcessor& p);
    ~PluginEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processor_ref_;

    ThemeButton theme_button_;
    Analyser    analyser_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
