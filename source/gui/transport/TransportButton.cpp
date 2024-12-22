#include "TransportButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
TransportButton::TransportButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id)
{
    setToggleState(GuiParams::INITIAL_ANALYSIS_STATE, juce::dontSendNotification);

    attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment >(apvts,
                                                                                           GuiParams::getName(param_id),
                                                                                           *this);

    onClick = [this]() { repaint(); };
}

/*---------------------------------------------------------------------------
**
*/
void
TransportButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    auto bounds = getImageBounds().toFloat();

    if (getToggleState()) {
        g.setColour(Theme::getColour(isEnabled() ? Theme::STOP_BUTTON : Theme::DISABLED_WIDGET));
        g.fillRoundedRectangle(bounds, 2.f);
    }
    else {
        g.setColour(Theme::getColour(isEnabled() ? Theme::RECORD_BUTTON : Theme::DISABLED_WIDGET));
        g.fillEllipse(bounds);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
TransportButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(isEnabled() ? juce::MouseCursor::PointingHandCursor : juce::MouseCursor::NormalCursor);
}

/*---------------------------------------------------------------------------
**
*/
juce::Rectangle< int >
TransportButton::getImageBounds() const
{
    const juce::Rectangle< int > bounds   = getLocalBounds();
    const int                    diameter = std::min(bounds.getWidth(), bounds.getHeight());
    const int                    radius   = static_cast< int >(std::floor(diameter * 0.5));

    return { bounds.getCentreX() - radius, bounds.getCentreY() - radius, diameter, diameter };
}

/*---------------------------------------------------------------------------
** End of File
*/
