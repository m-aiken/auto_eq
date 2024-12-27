#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class MeterDbScale : public juce::Component
{
public:
    explicit MeterDbScale(const Global::Meters::ORIENTATION meter_orientation);

    void paint(juce::Graphics& g) override;

private:
    Global::Meters::ORIENTATION meter_orientation_;
    int                         min_value_;
    int                         max_value_;
    uint8                       db_interval_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterDbScale)
};
