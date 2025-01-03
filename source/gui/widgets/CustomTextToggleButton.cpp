#include "CustomTextToggleButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
CustomTextToggleButton::CustomTextToggleButton(juce::AudioProcessorValueTreeState& apvts,
                                               const GuiParams::PARAM_ID           param_id,
                                               const bool                          initial_state,
                                               const juce::String&                 button_text)
    : CustomTextButton(button_text)
    , truthy_button_text_(button_text)
    , falsy_button_text_(button_text)
{
    init(apvts, param_id, initial_state);
}

/*---------------------------------------------------------------------------
**
*/
CustomTextToggleButton::CustomTextToggleButton(juce::AudioProcessorValueTreeState& apvts,
                                               const GuiParams::PARAM_ID           param_id,
                                               const bool                          initial_state,
                                               const juce::String&                 truthy_button_text,
                                               const juce::String&                 falsy_button_text)
    : CustomTextButton(initial_state ? truthy_button_text : falsy_button_text)
    , truthy_button_text_(truthy_button_text)
    , falsy_button_text_(falsy_button_text)
{
    init(apvts, param_id, initial_state);
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
**
*/
void
CustomTextToggleButton::init(juce::AudioProcessorValueTreeState& apvts,
                             const GuiParams::PARAM_ID           param_id,
                             const bool                          initial_state)
{
    setToggleable(true);
    setClickingTogglesState(true);
    setToggleState(initial_state, juce::dontSendNotification);

    attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment >(apvts,
                                                                                           GuiParams::getName(param_id),
                                                                                           *this);

    onClick = [this]() { handleClick(); };
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextToggleButton::handleClick()
{
    setButtonText(getToggleState() ? truthy_button_text_ : falsy_button_text_);
    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
