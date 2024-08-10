#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "GlobalConstants.h"
#include "SquareToggleButton.h"

class ButtonWithLabel : public juce::Component
{
public:
    ButtonWithLabel(juce::AudioProcessorValueTreeState& apvts,
                    GuiParams::PARAM_ID                 param_id,
                    const juce::String&                 label_text);

    void paint(juce::Graphics& g) override;
    void resized() override;

    SquareToggleButton& getButton();

private:
    SquareToggleButton button_;
    DisableableLabel   label_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonWithLabel)
};
