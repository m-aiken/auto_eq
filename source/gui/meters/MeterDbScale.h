#pragma once

#include <JuceHeader.h>

class MeterDbScale : public juce::Component
{
public:
    MeterDbScale();

    void paint(juce::Graphics& g) override;

private:
    int   min_value_;
    int   max_value_;
    uint8 db_interval_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterDbScale)
};
