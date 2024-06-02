#pragma once

#include "JuceHeader.h"

class MonoMeter
    : public juce::Component
    , public juce::Timer
{
public:
    MonoMeter(std::function< float() >&& callback_fn);
    ~MonoMeter() override;

    void paint(juce::Graphics& g) override;

    void timerCallback() override;

private:
    std::function< float() > getValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoMeter)
};
