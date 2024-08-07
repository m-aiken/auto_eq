#pragma once

#include <JuceHeader.h>

#include "MeterLabel.h"
#include "StereoMeter.h"
#include "PluginProcessor.h"

class MeterGroup : public juce::Component
{
public:
    MeterGroup(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    MeterLabel peak_label_;
    MeterLabel rms_label_;
    MeterLabel lufs_label_;

    StereoMeter peak_meters_;
    StereoMeter rms_meters_;
    StereoMeter lufs_meters_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterGroup)
};
