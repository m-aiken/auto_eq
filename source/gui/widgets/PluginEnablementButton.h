#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "GlobalConstants.h"

class PluginEnablementButton : public CustomTextButton
{
public:
    PluginEnablementButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id);

    void updateLabel();

private:
    std::unique_ptr< juce::AudioProcessorValueTreeState::ButtonAttachment > attachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEnablementButton)
};
