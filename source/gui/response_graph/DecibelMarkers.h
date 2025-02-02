#pragma once

#include <JuceHeader.h>

class DecibelMarkers : public juce::Component
{
public:
    DecibelMarkers();

    void paint(juce::Graphics& g) override;

private:
    int   min_value_;
    int   max_value_;
    uint8 db_interval_;

    static constexpr int X_PADDING = 8;
    static constexpr int Y_PADDING = 2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DecibelMarkers)
};
