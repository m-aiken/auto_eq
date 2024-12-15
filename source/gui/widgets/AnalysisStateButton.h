#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "GlobalConstants.h"

class AnalysisStateButton : public CustomTextButton
{
public:
    AnalysisStateButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id);

    void paint(Graphics& g) override;

    void updateLabel();

private:
    std::unique_ptr< juce::AudioProcessorValueTreeState::ButtonAttachment > attachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalysisStateButton)
};
