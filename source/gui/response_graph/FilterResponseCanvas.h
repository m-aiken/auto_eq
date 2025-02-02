#pragma once

#include <JuceHeader.h>

class FilterResponseCanvas : public juce::Component
{
public:
    FilterResponseCanvas() = default;

    void paint(juce::Graphics& g) override;

private:
    static bool shouldDrawFrequency(const int freq);
    static bool shouldBeBold(const int freq);

    static constexpr uint8 DB_INTERVAL = 3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseCanvas)
};
