#pragma once

#include <JuceHeader.h>

class FrequencyMarkers : public juce::Component
{
public:
    FrequencyMarkers();

    void paint(juce::Graphics& g) override;

private:
    static bool shouldDrawFrequency(const int freq);

    uint16 min_hz_;
    uint16 max_hz_;
    uint8  label_width_;

    static constexpr int X_LEFT_PADDING = 4;
    static constexpr int Y_PADDING      = 2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyMarkers)
};
