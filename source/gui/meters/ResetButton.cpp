#include "ResetButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
ResetButton::ResetButton(PluginProcessor& p)
    : juce::TextButton("RESET")
{
    onClick = [&]() { p.resetLufsModule(); };
}

/*---------------------------------------------------------------------------
**
*/
void
ResetButton::paintButton(Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    auto bounds = getLocalBounds();

    g.setColour(Theme::getColour(Theme::RECORD_BUTTON_ON));
    g.setFont(Theme::getFont());
    g.drawFittedText("RESET", 0, 0, bounds.getWidth(), bounds.getHeight(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
ResetButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);
}

/*---------------------------------------------------------------------------
** End of File
*/
