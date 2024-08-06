#pragma once

#include <JuceHeader.h>

#include "../widgets/DisableableLabel.h"
#include "../widgets/MenuButton.h"
#include "../widgets/RotaryControl.h"

class LimiterWidget
    : public juce::Component
    , public juce::Button::Listener
{
public:
    LimiterWidget(juce::AudioProcessorValueTreeState& apvts);
    ~LimiterWidget() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    MenuButton       enable_button_;
    DisableableLabel threshold_label_;
    RotaryControl    threshold_control_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LimiterWidget)
};
