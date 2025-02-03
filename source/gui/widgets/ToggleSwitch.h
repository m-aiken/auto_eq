#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class ToggleSwitch : public juce::ToggleButton
{
public:
    ToggleSwitch(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id);

    void paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down) override;
    void mouseEnter(const juce::MouseEvent& e) override;

private:
    std::unique_ptr< juce::AudioProcessorValueTreeState::ButtonAttachment > attachment_;

    static constexpr uint8 PADDING          = 4;
    static constexpr float BORDER_THICKNESS = 1.f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToggleSwitch)
};
