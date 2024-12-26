#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class ProfilerInputMeter
    : public juce::Component
    , public juce::Timer
{
public:
    explicit ProfilerInputMeter(PluginProcessor& p);
    ~ProfilerInputMeter() override;

    void paint(juce::Graphics& g) override;

    void timerCallback() override;

private:
    PluginProcessor& processor_ref_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProfilerInputMeter)
};
