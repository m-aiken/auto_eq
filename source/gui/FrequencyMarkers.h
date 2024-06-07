#pragma once

#include "JuceHeader.h"

class FrequencyMarkers : public juce::Component
{
public:
    FrequencyMarkers();

    void paint(juce::Graphics& g) override;

private:
    bool shouldDrawFrequency(int freq) const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyMarkers)
};
