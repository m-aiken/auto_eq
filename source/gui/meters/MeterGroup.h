#pragma once

#include "JuceHeader.h"

#include "MeterLabel.h"
#include "MonoMeter.h"
#include "../DecibelMarkers.h"
#include "../../PluginProcessor.h"

class MeterGroup : public juce::Component
{
public:
    MeterGroup(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DecibelMarkers db_scale_;

    MeterLabel peak_label_;
    MeterLabel rms_label_;
    MeterLabel lufs_label_;

    MonoMeter peak_meter_l_;
    MonoMeter peak_meter_r_;
    MonoMeter rms_meter_l_;
    MonoMeter rms_meter_r_;
    MonoMeter lufs_meter_l_;
    MonoMeter lufs_meter_r_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterGroup)
};
