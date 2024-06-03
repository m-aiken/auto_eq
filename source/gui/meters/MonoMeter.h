#pragma once

#include "JuceHeader.h"

#include "MeterCanvas.h"

class MonoMeter
    : public juce::Component
    , public juce::Timer
{
public:
    MonoMeter(std::function< float() >&& callback_fn);
    ~MonoMeter() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

private:
    std::function< float() > getValue;

    MeterCanvas backdrop_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoMeter)
};
