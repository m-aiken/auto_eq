#pragma once

#include <JuceHeader.h>

#include "MeterCanvas.h"
#include "PluginProcessor.h"
#include "GlobalConstants.h"

class MonoMeter
    : public juce::Component
    , public juce::Timer
{
public:
    MonoMeter(PluginProcessor& p, Global::Meters::METER_TYPE meter_type, Global::Channels::CHANNEL_ID channel);
    ~MonoMeter() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

private:
    PluginProcessor&             processor_ref_;
    Global::Meters::METER_TYPE   meter_type_;
    Global::Channels::CHANNEL_ID channel_;

    MeterCanvas backdrop_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoMeter)
};
