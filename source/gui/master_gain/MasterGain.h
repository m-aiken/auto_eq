#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "RotaryControl.h"
#include "MenuButton.h"

class MasterGain : public juce::Component
{
public:
    MasterGain(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DisableableLabel widget_label_;
    RotaryControl    rotary_control_;
    MenuButton       unity_gain_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasterGain)
};
