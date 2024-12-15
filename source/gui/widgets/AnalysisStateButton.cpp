#include "AnalysisStateButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
AnalysisStateButton::AnalysisStateButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id)
    : CustomTextButton("Analysis_State")
{
    setToggleable(true);
    setClickingTogglesState(true);
    setToggleState(GuiParams::INITIAL_ANALYSIS_STATE, juce::dontSendNotification);
    setButtonText(GuiParams::INITIAL_ANALYSIS_STATE ? "Stop Analysis" : "Start Analysis");

    attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment >(apvts,
                                                                                           GuiParams::getName(param_id),
                                                                                           *this);

    onClick = [this]() { updateLabel(); };
}

/*---------------------------------------------------------------------------
**
*/
void
AnalysisStateButton::paint(Graphics& g)
{
    // Draw the standard button first.
    CustomTextButton::paintButton(g, true, false);

    // Then draw a red border if the analysis is active.
    if (getToggleState()) {
        g.setColour(Theme::RED_ORANGE);
        g.drawRect(getLocalBounds(), 1);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
AnalysisStateButton::updateLabel()
{
    setButtonText(getToggleState() ? "Stop Analysis" : "Start Analysis");

    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
