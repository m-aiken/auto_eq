#pragma once

#include <JuceHeader.h>

#include "SpinBoxButton.h"
#include "SpinBoxTextBox.h"

class SpinBox : public juce::Component
{
public:
    SpinBox(juce::Range< double > range, double default_value = 0.0, const juce::String& unit = "");

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    SpinBoxTextBox value_box_;
    juce::Label    unit_label_;
    SpinBoxButton  up_button_;
    SpinBoxButton  down_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpinBox)
};
