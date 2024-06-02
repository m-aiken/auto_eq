#pragma once

#include "JuceHeader.h"
#include "MonoMeter.h"
#include "../DecibelMarkers.h"
#include "../../PluginProcessor.h"
#include "../../utility/GlobalConstants.h"

class StereoMeter : public juce::Component
{
public:
    StereoMeter(Global::METER_TYPE meter_type, PluginProcessor& p);

    void resized() override;

private:
    MonoMeter      meter_l_;
    DecibelMarkers db_scale_;
    MonoMeter      meter_r_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StereoMeter)
};
