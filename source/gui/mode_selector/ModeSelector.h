#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "ToggleSwitch.h"

class ModeSelector : public juce::Component
{
public:
    explicit ModeSelector(/*juce::AudioProcessorValueTreeState& apvts*/);

    void resized() override;

    ToggleSwitch& getToggleSwitch();

private:
    DisableableLabel analyser_mode_label_;
    DisableableLabel profiler_mode_label_;
    ToggleSwitch     toggle_switch_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModeSelector)
};
