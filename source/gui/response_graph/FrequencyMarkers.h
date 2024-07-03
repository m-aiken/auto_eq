#pragma once

#include <JuceHeader.h>

class FrequencyMarkers : public juce::Component
{
public:
    FrequencyMarkers();

    void paint(juce::Graphics& g) override;

private:
    bool shouldDrawFrequency(int freq) const;

    uint16 min_hz_;
    uint16 max_hz_;
    uint8  label_width_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyMarkers)
};
