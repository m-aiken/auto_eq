#include "PowerButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
PowerButton::PowerButton(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id)
    : juce::ToggleButton()
{
    attachment_.reset(
        new juce::AudioProcessorValueTreeState::ButtonAttachment(apvts, GuiParams::getName(param_id), *this));
}

/*---------------------------------------------------------------------------
**
*/
void
PowerButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif

    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    const uint8            button_margin = 12;
    juce::Rectangle< int > bounds        = getLocalBounds();
    int                    bounds_height = bounds.getHeight();
    int                    centre_x      = bounds.getCentreX();

    juce::Rectangle< float > button_bounds(0, 0, bounds.getHeight(), bounds.getHeight());

    // Reduce the drawable bounds slightly so that the ellipse isn't clipped at the top/left/bottom/right edges.
    button_bounds = button_bounds.withSizeKeepingCentre(button_bounds.getWidth() - button_margin,
                                                        button_bounds.getHeight() - button_margin);

    // Ellipse.
    g.setColour(Theme::getColour(getToggleState() ? Theme::POWER_BUTTON_ON : Theme::POWER_BUTTON_OFF));
    g.drawEllipse(button_bounds, 2.f);

    // Break in the ellipse (rectangle the same colour as the main background so that it's not seen).
    int                    invisible_rect_width = 6;
    juce::Rectangle< int > invisible_rect(centre_x - (invisible_rect_width * 0.5),
                                          0,
                                          invisible_rect_width,
                                          bounds_height * 0.5);

    g.setColour(Theme::getColour(Theme::MAIN_BG));
    g.fillRect(invisible_rect);

    // Vertical line.
    int                    vertical_line_width = 2;
    juce::Rectangle< int > vertical_line(centre_x - (vertical_line_width * 0.5),
                                         button_bounds.getY(),
                                         vertical_line_width,
                                         static_cast< int >(std::floor(bounds_height * 0.25)));

    g.setColour(Theme::getColour(getToggleState() ? Theme::POWER_BUTTON_ON : Theme::POWER_BUTTON_OFF));
    g.fillRect(vertical_line);
}

/*---------------------------------------------------------------------------
**
*/
void
PowerButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);
}

/*---------------------------------------------------------------------------
** End of File
*/
