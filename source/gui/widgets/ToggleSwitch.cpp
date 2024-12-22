#include "Theme.h"
#include "ToggleSwitch.h"

/*---------------------------------------------------------------------------
**
*/
ToggleSwitch::ToggleSwitch(/*juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id*/)
    : juce::ToggleButton()
{
#if 0
    attachment_.reset(
        new juce::AudioProcessorValueTreeState::ButtonAttachment(apvts, GuiParams::getName(param_id), *this));
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
ToggleSwitch::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif

    juce::Rectangle< int > bounds         = getLocalBounds();
    const uint8            padding        = 4;
    const uint8            thumb_diameter = bounds.getHeight() - (padding * 2);

    g.setColour(Theme::getColour(isEnabled() ? Theme::CHECKBOX : Theme::DISABLED_WIDGET));
    g.drawRoundedRectangle(bounds.toFloat(), thumb_diameter, 1.f);

    int x = padding;

    if (getToggleState()) {
        x = bounds.getRight() - thumb_diameter - padding;
    }

    const juce::Rectangle< float > thumb(x, padding, thumb_diameter, thumb_diameter);

    g.fillEllipse(thumb);
}

/*---------------------------------------------------------------------------
**
*/
void
ToggleSwitch::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(isEnabled() ? juce::MouseCursor::PointingHandCursor : juce::MouseCursor::NormalCursor);
}

/*---------------------------------------------------------------------------
** End of File
*/
