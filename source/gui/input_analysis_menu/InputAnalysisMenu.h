#pragma once

#include <JuceHeader.h>

#include "../widgets/RecordButton.h"
#include "../../PluginProcessor.h"

class InputAnalysisMenu
    : public juce::Component
    , public juce::Button::Listener
{
public:
    InputAnalysisMenu(PluginProcessor& processor_ref);
    ~InputAnalysisMenu() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    RecordButton analyse_input_button_;

    PluginProcessor& processor_ref_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputAnalysisMenu)
};
