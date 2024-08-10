#pragma once

#include <JuceHeader.h>

#include "ButtonWithLabel.h"
#include "DisableableLabel.h"
#include "PluginProcessor.h"
#include "RotaryControl.h"

class MasterGain
    : public juce::Component
    , public juce::Button::Listener
{
public:
    MasterGain(PluginProcessor& p);
    ~MasterGain() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    DisableableLabel widget_label_;
    RotaryControl    rotary_control_;
    ButtonWithLabel  unity_gain_button_;

    PluginProcessor& processor_ref_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasterGain)
};
