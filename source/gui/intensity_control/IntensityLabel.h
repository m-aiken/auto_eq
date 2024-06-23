#pragma once

#include <JuceHeader.h>

class IntensityLabel : public juce::Label
{
public:
    IntensityLabel();

    void paint(juce::Graphics& g) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntensityLabel)
};
