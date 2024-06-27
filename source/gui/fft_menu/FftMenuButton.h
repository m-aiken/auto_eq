#pragma once

#include <JuceHeader.h>

#include "../../utility/GlobalConstants.h"

class FftMenuButton : public juce::ToggleButton
{
public:
    FftMenuButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id);

private:
    std::unique_ptr< juce::AudioProcessorValueTreeState::ButtonAttachment > attachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FftMenuButton)
};
