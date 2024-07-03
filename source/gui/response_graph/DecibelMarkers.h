#pragma once

#include <JuceHeader.h>

class DecibelMarkers : public juce::Component
{
public:
    DecibelMarkers();

    void paint(juce::Graphics& g) override;

private:
    float min_value_;
    float max_value_;
    uint8 db_interval_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DecibelMarkers)
};
