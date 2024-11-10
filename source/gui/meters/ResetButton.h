#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class ResetButton : public juce::TextButton
{
public:
    explicit ResetButton(PluginProcessor& p);

    void paintButton(Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down) override;
    void mouseEnter(const juce::MouseEvent& e) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ResetButton)
};
