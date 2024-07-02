#include "FftMenuButton.h"
#include "../look_and_feel/Theme.h"

/*---------------------------------------------------------------------------
**
*/
FftMenuButton::FftMenuButton(const juce::String&                 label_text,
                             juce::AudioProcessorValueTreeState& apvts,
                             GuiParams::PARAM_ID                 param_id)
    : juce::ToggleButton(label_text)
{
    attachment_.reset(
        new juce::AudioProcessorValueTreeState::ButtonAttachment(apvts, GuiParams::getName(param_id), *this));
}

/*---------------------------------------------------------------------------
**
*/
void
FftMenuButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    const uint8            padding = 4;
    juce::Rectangle< int > bounds  = getLocalBounds();
    juce::Rectangle< int > button_bounds(0, 0, bounds.getHeight(), bounds.getHeight());
    juce::Rectangle< int > label_bounds(button_bounds.getRight() + (padding * 2),
                                        0,
                                        bounds.getWidth() - button_bounds.getWidth(),
                                        bounds.getHeight());

    g.setColour(Theme::getColour(Theme::CHECKBOX));
    g.drawRect(button_bounds);

    if (getToggleState()) {
        g.fillRect(button_bounds.withSizeKeepingCentre(button_bounds.getWidth() - padding,
                                                       button_bounds.getHeight() - padding));
    }

    g.setColour(Theme::getColour(Theme::TEXT));
    g.setFont(Theme::getFont());
    g.drawFittedText(getButtonText(), label_bounds, juce::Justification::centredLeft, 1.f);
}

/*---------------------------------------------------------------------------
**
*/
void
FftMenuButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);
}

/*---------------------------------------------------------------------------
** End of File
*/
