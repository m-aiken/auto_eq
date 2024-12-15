#include "PluginEnablementButton.h"

/*---------------------------------------------------------------------------
**
*/
PluginEnablementButton::PluginEnablementButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id)
    : CustomTextButton("Plugin_Enablement")
{
    setToggleable(true);
    setClickingTogglesState(true);
    setToggleState(GuiParams::INITIAL_POWER_STATE, juce::dontSendNotification);
    setButtonText(GuiParams::INITIAL_POWER_STATE ? "Disable" : "Enable");

    attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment >(apvts,
                                                                                           GuiParams::getName(param_id),
                                                                                           *this);

    onClick = [this]() { updateLabel(); };
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEnablementButton::updateLabel()
{
    setButtonText(getToggleState() ? "Disable" : "Enable");

    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
