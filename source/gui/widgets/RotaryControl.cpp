#include "RotaryControl.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
RotaryControl::RotaryControl(juce::AudioProcessorValueTreeState& apvts,
                             GuiParams::PARAM_ID                 parameter_id,
                             bool                                draw_text_value,
                             juce::String                        suffix,
                             int                                 num_decimal_places)
    : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , param_(apvts.getParameter(GuiParams::getName(parameter_id)))
    , draw_text_value_(draw_text_value)
    , suffix_(suffix)
    , num_decimal_places_(num_decimal_places)
{
    slider_attachment_.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, GuiParams::getName(parameter_id), *this));

    if (param_ != nullptr) {
        param_->addListener(this);
    }

    setMouseCursor(juce::MouseCursor::UpDownLeftRightResizeCursor);
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

    auto bounds = getLocalBounds();

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
    juce::String value_str(getValue(), num_decimal_places_);

    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));
    g.setFont(Theme::getFont());
    g.drawFittedText(value_str + " " + suffix_, bounds, juce::Justification::centred, 1);
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
RotaryControl::getNormalisedValue()
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
