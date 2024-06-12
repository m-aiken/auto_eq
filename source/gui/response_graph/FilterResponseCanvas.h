#pragma once

#include <JuceHeader.h>

class FilterResponseCanvas : public juce::Component
{
public:
    FilterResponseCanvas() = default;

    void paint(juce::Graphics& g) override;

private:
    bool shouldDrawFrequency(int freq) const;
    bool shouldBeBold(int freq) const;

    static const uint8 DB_INTERVAL;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseCanvas)
};
