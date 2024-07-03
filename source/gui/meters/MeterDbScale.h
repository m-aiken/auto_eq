#pragma once

#include <JuceHeader.h>

class MeterDbScale : public juce::Component
{
public:
    MeterDbScale();

    void paint(juce::Graphics& g) override;

private:
    float min_value_;
    float max_value_;
    uint8 db_interval_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterDbScale)
};
