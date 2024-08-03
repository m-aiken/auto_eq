#pragma once

#include <JuceHeader.h>

#include "../widgets/DisableableLabel.h"
#include "../widgets/MenuButton.h"
#include "../widgets/spinbox/SpinBox.h"

class UnityGainWidget
    : public juce::Component
    , public juce::Button::Listener
{
public:
    UnityGainWidget(juce::AudioProcessorValueTreeState& apvts);
    ~UnityGainWidget() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    MenuButton       enable_button_;
    DisableableLabel gain_selector_label_;
    SpinBox          gain_selector_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UnityGainWidget)
};
