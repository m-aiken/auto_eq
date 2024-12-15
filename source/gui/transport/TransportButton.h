#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class TransportButton : public juce::ToggleButton
{
public:
    TransportButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id);

    void paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down) override;
    void mouseEnter(const juce::MouseEvent& e) override;

private:
    [[nodiscard]] juce::Rectangle< int > getImageBounds() const;

    std::unique_ptr< juce::AudioProcessorValueTreeState::ButtonAttachment > attachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportButton)
};
