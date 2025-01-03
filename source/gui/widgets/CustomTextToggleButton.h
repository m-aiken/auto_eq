#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "GlobalConstants.h"

class CustomTextToggleButton : public CustomTextButton
{
public:
    CustomTextToggleButton(juce::AudioProcessorValueTreeState& apvts,
                           const GuiParams::PARAM_ID           param_id,
                           const bool                          initial_state,
                           const juce::String&                 button_text);

    CustomTextToggleButton(juce::AudioProcessorValueTreeState& apvts,
                           const GuiParams::PARAM_ID           param_id,
                           const bool                          initial_state,
                           const juce::String&                 truthy_button_text,
                           const juce::String&                 falsy_button_text);

    void paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down) override;

private:
    void init(juce::AudioProcessorValueTreeState& apvts, const GuiParams::PARAM_ID param_id, const bool initial_state);
    void handleClick();

    std::unique_ptr< juce::AudioProcessorValueTreeState::ButtonAttachment > attachment_;

    const juce::String truthy_button_text_;
    const juce::String falsy_button_text_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomTextToggleButton)
};
