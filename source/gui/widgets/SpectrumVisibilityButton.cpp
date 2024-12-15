#include "SpectrumVisibilityButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
SpectrumVisibilityButton::SpectrumVisibilityButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id)
    : CustomTextButton("Spectrum_Visibility")
{
    setToggleable(true);
    setClickingTogglesState(true);
    setToggleState(GuiParams::INITIAL_FFT_STATE, juce::dontSendNotification);
    setButtonText(GuiParams::INITIAL_FFT_STATE ? "Hide FFT" : "Show FFT");

    attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment >(apvts,
                                                                                           GuiParams::getName(param_id),
                                                                                           *this);

    onClick = [this]() { updateLabel(); };
}

/*---------------------------------------------------------------------------
**
*/
void
SpectrumVisibilityButton::updateLabel()
{
    setButtonText(getToggleState() ? "Hide FFT" : "Show FFT");

    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
