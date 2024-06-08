#pragma once

#include <JuceHeader.h>

class MeterDbScale : public juce::Component
{
public:
    MeterDbScale();

    void paint(juce::Graphics& g) override;

private:
    static const uint8 DB_INTERVAL;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterDbScale)
};
