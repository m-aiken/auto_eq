#pragma once

#include <JuceHeader.h>

class IntensityLabel : public juce::Label
{
public:
    IntensityLabel(const juce::String& text, const juce::Justification justification = juce::Justification::centred);

    void paint(juce::Graphics& g) override;

private:
    juce::Justification justification_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntensityLabel)
};
