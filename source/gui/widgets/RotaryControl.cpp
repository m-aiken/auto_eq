#include "RotaryControl.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
RotaryControl::RotaryControl(juce::AudioProcessorValueTreeState& apvts, const juce::String& parameter_id)
    : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , param_(apvts.getParameter(parameter_id))
{
    slider_attachment_.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, parameter_id, *this));

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
    if (Global::SHOW_DEBUG_BOUNDS) {
        g.setColour(juce::Colours::green);
        g.drawRect(getLocalBounds());
    }

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
