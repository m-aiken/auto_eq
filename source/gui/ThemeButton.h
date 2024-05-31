#pragma once

#include <JuceHeader.h>

class ThemeButton : public juce::ToggleButton
{
public:
    ThemeButton();

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThemeButton)
};
