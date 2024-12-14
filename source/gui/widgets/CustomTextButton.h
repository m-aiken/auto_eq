#pragma once

#include <JuceHeader.h>

#include "Theme.h"

class CustomTextButton : public juce::TextButton
{
public:
    explicit CustomTextButton(const juce::String& label_text);

    void paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down) override;
    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit(const juce::MouseEvent& e) override;

private:
    Theme::DarkLightPair background_colour_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomTextButton)
};
