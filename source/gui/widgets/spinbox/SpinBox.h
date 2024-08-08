#pragma once

#include <JuceHeader.h>

#include "SpinBoxButton.h"
#include "SpinBoxTextBox.h"

class SpinBox
    : public juce::Component
    , public juce::Button::Listener
{
public:
    SpinBox(juce::RangedAudioParameter* param, float interval = 0.1f);
    ~SpinBox() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    float interval_;

    SpinBoxTextBox value_box_;
    SpinBoxButton  up_button_;
    SpinBoxButton  down_button_;

    juce::RangedAudioParameter* param_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpinBox)
};
