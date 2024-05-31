#pragma once

#include <JuceHeader.h>

class DecibelMarkers : public juce::Component
{
public:
    DecibelMarkers();

    void paint(juce::Graphics& g) override;

private:
    static const uint8 DB_INTERVAL;

    juce::Font font_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DecibelMarkers)
};
