#include "RecordButton.h"
#include "../look_and_feel/Theme.h"

/*---------------------------------------------------------------------------
**
*/
RecordButton::RecordButton(const juce::String&                 label_text,
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
RecordButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif

    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    const uint8              button_margin = 12;
    const uint8              padding       = 4;
    juce::Rectangle< int >   bounds        = getLocalBounds();
    juce::Rectangle< float > button_bounds(0, 0, bounds.getHeight(), bounds.getHeight());
    juce::Rectangle< int >   label_bounds(button_bounds.getRight(),
                                        0,
                                        bounds.getWidth() - button_bounds.getWidth(),
                                        bounds.getHeight());
    
    button_bounds = button_bounds.withSizeKeepingCentre(button_bounds.getWidth() - button_margin,
                                                        button_bounds.getHeight() - button_margin);

    // Draw the two ellipses (outline and fill).
    g.setColour(Theme::getColour(getToggleState() ? Theme::RECORD_BUTTON_ON : Theme::RECORD_BUTTON_OFF));

    g.drawEllipse(button_bounds, 1.f);

    g.fillEllipse(
        button_bounds.withSizeKeepingCentre(button_bounds.getWidth() - padding, button_bounds.getHeight() - padding));

    // Draw the label.
    g.setColour(Theme::getColour(Theme::TEXT));
    g.setFont(Theme::getFont());
    g.drawFittedText(getButtonText(), label_bounds, juce::Justification::centredLeft, 1.f);
}

/*---------------------------------------------------------------------------
**
*/
void
RecordButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);
}

/*---------------------------------------------------------------------------
** End of File
*/
