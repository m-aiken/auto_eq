#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"
#include "MeterCanvas.h"
#include "PluginProcessor.h"

class MonoMeter
    : public juce::Component
    , public juce::Timer
{
public:
    MonoMeter(PluginProcessor&                  p,
              const Global::Meters::METER_TYPE  meter_type,
              const Global::Meters::ORIENTATION meter_orientation,
              const double                      meter_width_pct = 100.0);
    ~MonoMeter() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

private:
    PluginProcessor&            processor_ref_;
    Global::Meters::METER_TYPE  meter_type_;
    Global::Meters::ORIENTATION meter_orientation_;
    const double                meter_width_pct_;

    MeterCanvas backdrop_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoMeter)
};
