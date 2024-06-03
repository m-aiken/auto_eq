#pragma once

#include "JuceHeader.h"

class MeterLabel : public juce::Component
{
public:
    MeterLabel(const juce::String& text);

    void paint(juce::Graphics& g) override;

private:
    juce::String text_;
    juce::Font   font_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterLabel)
};
