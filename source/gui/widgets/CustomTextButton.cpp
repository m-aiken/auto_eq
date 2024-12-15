#include "CustomTextButton.h"

/*---------------------------------------------------------------------------
**
*/
CustomTextButton::CustomTextButton(const juce::String& label_text)
    : juce::TextButton(label_text + "_button")
{
    setButtonText(label_text);

    background_colour_ = Theme::TEXT_BTN_BG;
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    g.fillAll(Theme::getColour(background_colour_));
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));
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

    setMouseCursor(isEnabled() ? juce::MouseCursor::PointingHandCursor : juce::MouseCursor::NormalCursor);

    if (isEnabled()) {
        background_colour_ = Theme::TEXT_BTN_BG_FOCUS;

        repaint();
    }
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextButton::mouseExit(const juce::MouseEvent& e)
{
    if (!isEnabled()) {
        return;
    }

    juce::ignoreUnused(e);

    background_colour_ = Theme::TEXT_BTN_BG;

    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
