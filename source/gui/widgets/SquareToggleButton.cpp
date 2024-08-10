#include "SquareToggleButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
SquareToggleButton::SquareToggleButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id)
    : juce::ToggleButton()
{
    attachment_.reset(
        new juce::AudioProcessorValueTreeState::ButtonAttachment(apvts, GuiParams::getName(param_id), *this));
}

/*---------------------------------------------------------------------------
**
*/
void
SquareToggleButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif

    juce::Rectangle< int > bounds  = getLocalBounds();
    const uint8            padding = 4;

    g.setColour(Theme::getColour(isEnabled() ? Theme::CHECKBOX : Theme::DISABLED_WIDGET));
    g.drawRect(bounds);

    if (getToggleState()) {
        g.fillRect(bounds.withSizeKeepingCentre(bounds.getWidth() - padding, bounds.getHeight() - padding));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
SquareToggleButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);
}

/*---------------------------------------------------------------------------
** End of File
*/
