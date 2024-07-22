#pragma once

#include <JuceHeader.h>

#include "../widgets/MenuButton.h"
#include "../widgets/spinbox/SpinBox.h"

class UnityGainWidget : public juce::Component
{
public:
    UnityGainWidget(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    MenuButton  enable_button_;
    juce::Label gain_selector_label_;
    SpinBox     gain_selector_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UnityGainWidget)
};
