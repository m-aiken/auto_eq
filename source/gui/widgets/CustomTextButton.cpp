#include "CustomTextButton.h"

/*---------------------------------------------------------------------------
**
*/
CustomTextButton::CustomTextButton(const juce::String& label_text)
    : juce::TextButton("profile_" + label_text + "_button")
{
    setButtonText(label_text);

    background_colour_ = Theme::PROFILE_BUTTON_NO_FOCUS;
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    g.fillAll(Theme::getColour(background_colour_));
    g.setColour(Theme::getColour(Theme::TEXT));
    g.setFont(Theme::getFont());
    g.drawFittedText(getButtonText(), getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);

    background_colour_ = Theme::PROFILE_BUTTON_FOCUS;

    repaint();
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextButton::mouseExit(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    background_colour_ = Theme::PROFILE_BUTTON_NO_FOCUS;

    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
