#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "GlobalConstants.h"

class CustomTextToggleButton : public CustomTextButton
{
public:
    CustomTextToggleButton(juce::AudioProcessorValueTreeState& apvts,
                           const GuiParams::PARAM_ID           param_id,
                           const juce::String&                 button_text,
                           const bool                          initial_state);

    void paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down) override;

private:
    std::unique_ptr< juce::AudioProcessorValueTreeState::ButtonAttachment > attachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomTextToggleButton)
};
