#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "RotaryControl.h"

class EqIntensity : public juce::Component
{
public:
    explicit EqIntensity(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DisableableLabel widget_label_;
    RotaryControl    rotary_control_;
    DisableableLabel off_label_;
    DisableableLabel full_label_;

    static constexpr int PADDING = 12;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqIntensity)
};
