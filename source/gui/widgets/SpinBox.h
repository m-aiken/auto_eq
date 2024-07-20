#pragma once

#include <JuceHeader.h>

class SpinBox : public juce::Slider
{
public:
    SpinBox(juce::Range< double > range, double default_value = 0.0, const juce::String& unit = "");

    void paint(juce::Graphics& g) override;

private:
    juce::String unit_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpinBox)
};
