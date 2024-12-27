#pragma once

#include <JuceHeader.h>

#include "MeterDbScale.h"
#include "MonoMeter.h"

class ProfilerInputWidget : public juce::Component
{
public:
    explicit ProfilerInputWidget(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    MeterDbScale db_scale_;
    MonoMeter    meter_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProfilerInputWidget)
};
