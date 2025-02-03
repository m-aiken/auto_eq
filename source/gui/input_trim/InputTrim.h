#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "RotaryControl.h"

class InputTrim : public juce::Component
{
public:
    explicit InputTrim(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DisableableLabel widget_label_;
    RotaryControl    rotary_control_;
    DisableableLabel min_label_;
    DisableableLabel max_label_;

    static constexpr int PADDING = 12;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputTrim)
};
