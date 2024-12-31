#include "Theme.h"
#include "ToggleSwitch.h"

/*---------------------------------------------------------------------------
**
*/
ToggleSwitch::ToggleSwitch(juce::AudioProcessorValueTreeState& apvts, GuiParams::PARAM_ID param_id)
    : juce::ToggleButton()
{
    attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment >(apvts,
                                                                                           GuiParams::getName(param_id),
                                                                                           *this);

    juce::RangedAudioParameter* param = apvts.getParameter(GuiParams::getName(param_id));

    if (param != nullptr) {
        setToggleState(static_cast< bool >(param->getValue()), juce::dontSendNotification);
    }
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

    const juce::Rectangle< int >   bounds           = getLocalBounds();
    const juce::Rectangle< float > float_bounds     = bounds.toFloat();
    constexpr uint8                padding          = 4;
    constexpr float                border_thickness = 1.f;
    const uint8                    thumb_diameter   = bounds.getHeight() - (padding * 2);

    g.setColour(Theme::getColour(isEnabled() ? Theme::CHECKBOX : Theme::DISABLED_WIDGET));
    g.drawRoundedRectangle(float_bounds.withSizeKeepingCentre(float_bounds.getWidth() - border_thickness,
                                                              float_bounds.getHeight() - border_thickness),
                           thumb_diameter,
                           border_thickness);

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
