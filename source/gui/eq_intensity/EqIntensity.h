#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "PluginProcessor.h"
#include "RotaryControl.h"

class EqIntensity : public juce::Component
{
public:
    EqIntensity(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DisableableLabel widget_label_;
    RotaryControl    rotary_control_;
    DisableableLabel off_label_;
    DisableableLabel full_label_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqIntensity)
};
