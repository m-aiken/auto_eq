#pragma once

#include <JuceHeader.h>

class SpinBoxTextBox : public juce::Label
{
public:
    SpinBoxTextBox();

    void paint(juce::Graphics& g) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpinBoxTextBox)
};
