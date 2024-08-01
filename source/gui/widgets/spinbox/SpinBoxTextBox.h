#pragma once

#include <JuceHeader.h>

class SpinBoxTextBox : public juce::Label
{
public:
    SpinBoxTextBox(juce::RangedAudioParameter* param);

    void paint(juce::Graphics& g) override;

private:
    juce::RangedAudioParameter* param_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpinBoxTextBox)
};
