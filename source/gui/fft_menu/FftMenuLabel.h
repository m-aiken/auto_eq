#pragma once

#include <JuceHeader.h>

class FftMenuLabel : public juce::Label
{
public:
    FftMenuLabel(const juce::String& text);

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FftMenuLabel)
};
