#pragma once

#include <JuceHeader.h>

#include "RotaryControl.h"

class ProfilerInputWidget : public juce::Component
{
public:
    explicit ProfilerInputWidget(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    RotaryControl input_trim_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProfilerInputWidget)
};
