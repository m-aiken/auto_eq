#include "RotaryControl.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
RotaryControl::RotaryControl(juce::AudioProcessorValueTreeState& apvts,
                             const GuiParams::PARAM_ID           parameter_id,
                             const bool                          draw_text_value,
                             juce::String                        suffix,
                             const int                           num_decimal_places)
    : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , param_(apvts.getParameter(GuiParams::getName(parameter_id)))
    , draw_text_value_(draw_text_value)
    , suffix_(std::move(suffix))
    , num_decimal_places_(num_decimal_places)
{
    slider_attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment >(apvts,
                                                                                                  GuiParams::getName(
                                                                                                      parameter_id),
                                                                                                  *this);

    if (param_ != nullptr) {
        param_->addListener(this);
    }
}

/*---------------------------------------------------------------------------
**
*/
RotaryControl::~RotaryControl()
{
    if (param_ != nullptr) {
        param_->removeListener(this);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::green);
    g.drawRect(getLocalBounds());
#endif

    const auto bounds = getLocalBounds();

    getLookAndFeel().drawRotarySlider(g,
                                      bounds.getX(),
                                      bounds.getY(),
                                      bounds.getWidth(),
                                      bounds.getHeight(),
                                      getNormalisedValue(),
                                      START_ANGLE,
                                      END_ANGLE,
                                      *this);

    if (!draw_text_value_) {
        return;
    }

    // Value text.
    const juce::String value_str(getValue(), num_decimal_places_);

    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));
    g.setFont(Theme::getFont());
    g.drawFittedText(value_str + " " + suffix_, bounds, juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(isEnabled() ? juce::MouseCursor::UpDownLeftRightResizeCursor : juce::MouseCursor::NormalCursor);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::parameterValueChanged(int parameter_index, float new_value)
{
    juce::ignoreUnused(parameter_index, new_value);

    repaint();
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::parameterGestureChanged(int parameter_index, bool gesture_is_starting)
{
    // Only implemented because it's pure virtual.
    juce::ignoreUnused(parameter_index, gesture_is_starting);
}

/*---------------------------------------------------------------------------
**
*/
float
RotaryControl::getNormalisedValue() const
{
    if (param_ == nullptr) {
        return 0.f;
    }

    juce::NormalisableRange< float > range = param_->getNormalisableRange();

    return juce::jmap< float >(static_cast< float >(getValue()), range.start, range.end, START_ANGLE, END_ANGLE);
}

/*---------------------------------------------------------------------------
** End of File
*/
