#include "CustomTextToggleButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
CustomTextToggleButton::CustomTextToggleButton(juce::AudioProcessorValueTreeState& apvts,
                                               const GuiParams::PARAM_ID           param_id,
                                               const juce::String&                 button_text,
                                               const bool                          initial_state)
    : CustomTextButton(button_text)
{
    setToggleable(true);
    setClickingTogglesState(true);
    setToggleState(initial_state, juce::dontSendNotification);

    attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment >(apvts,
                                                                                           GuiParams::getName(param_id),
                                                                                           *this);

    onClick = [this]() { repaint(); };
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextToggleButton::paintButton(juce::Graphics& g,
                                    bool            should_draw_button_as_highlighted,
                                    bool            should_draw_button_as_down)
{
    // Draw the regular button first.
    CustomTextButton::paintButton(g, should_draw_button_as_highlighted, should_draw_button_as_down);

    // The draw a coloured border if we're in the "on" state.
    if (getToggleState() && isEnabled()) {
        g.setColour(Theme::getColour(Theme::TEXT_BTN_TOGGLE_ON_BORDER));
        g.drawRect(getLocalBounds());
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
