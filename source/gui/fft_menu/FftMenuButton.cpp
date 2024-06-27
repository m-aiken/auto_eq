#include "FftMenuButton.h"

/*---------------------------------------------------------------------------
**
*/
FftMenuButton::FftMenuButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id)
    : juce::ToggleButton()
{
    attachment_.reset(
        new juce::AudioProcessorValueTreeState::ButtonAttachment(apvts, GuiParams::getName(param_id), *this));
}

/*---------------------------------------------------------------------------
** End of File
*/
