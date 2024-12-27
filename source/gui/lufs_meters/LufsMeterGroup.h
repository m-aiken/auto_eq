#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"
#include "MonoMeter.h"
#include "PluginProcessor.h"

class LufsMeterGroup : public juce::Component
{
public:
    explicit LufsMeterGroup(PluginProcessor& p);

    void resized() override;

private:
    void initMeter(PluginProcessor& p, Global::Meters::METER_TYPE meter_type);

    std::array< std::unique_ptr< MonoMeter >, Global::Meters::NUM_LOUDNESS_METERS > meters_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LufsMeterGroup)
};
