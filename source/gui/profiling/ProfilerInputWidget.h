#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "ProfilerInputMeter.h"
#include "RotaryControl.h"

class ProfilerInputWidget : public juce::Component
{
public:
    explicit ProfilerInputWidget(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DisableableLabel   label_;
    ProfilerInputMeter meter_;
    RotaryControl      input_trim_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProfilerInputWidget)
};
