#pragma once

#include <JuceHeader.h>

class MeterCanvas : public juce::Component
{
public:
    MeterCanvas();

    void paint(juce::Graphics& g) override;

private:
    static const uint8 DB_INTERVAL;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterCanvas)
};
