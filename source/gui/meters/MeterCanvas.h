#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class MeterCanvas : public juce::Component
{
public:
    explicit MeterCanvas(const Global::Meters::ORIENTATION meter_orientation);

    void paint(juce::Graphics& g) override;

private:
    Global::Meters::ORIENTATION meter_orientation_;
    static const uint8          DB_INTERVAL;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterCanvas)
};
