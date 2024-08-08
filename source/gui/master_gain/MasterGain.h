#pragma once

#include <JuceHeader.h>

class MasterGain : public juce::Component
{
public:
    MasterGain();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasterGain)
};
