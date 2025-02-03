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

    static constexpr int DB_INTERVAL  = 6;
    static constexpr int LABEL_WIDTH  = 40;
    static constexpr int LABEL_HEIGHT = 20;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterDbScale)
};
