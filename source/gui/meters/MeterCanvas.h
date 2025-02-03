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

    static constexpr uint8 DB_INTERVAL    = 3;
    static constexpr uint8 LINE_THICKNESS = 1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterCanvas)
};
