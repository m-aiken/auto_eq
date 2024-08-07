#include "EqBandSlider.h"
#include "GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
EqBandSlider::EqBandSlider(juce::AudioProcessorValueTreeState& apvts, const juce::String& parameter_id)
    : juce::Slider(juce::Slider::LinearVertical, juce::Slider::NoTextBox)
    , param_(apvts.getParameter(parameter_id))
{
    slider_attachment_.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, parameter_id, *this));

    if (param_ != nullptr) {
        param_->addListener(this);
    }

    setRange(Global::MAX_DB_CUT, Global::MAX_DB_BOOST);
    setMouseCursor(juce::MouseCursor::DraggingHandCursor);
}

/*---------------------------------------------------------------------------
**
*/
EqBandSlider::~EqBandSlider()
{
    if (param_ != nullptr) {
        param_->removeListener(this);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
EqBandSlider::paint(juce::Graphics& g)
{
    if (param_ == nullptr) {
        return;
    }

    juce::Rectangle< float > bounds        = getLocalBounds().toFloat();
    float                    bounds_y      = bounds.getY();
    float                    bounds_bottom = bounds.getBottom();
    float                    param_value   = param_->convertFrom0to1(param_->getValue());

    float val = juce::jmap< float >(param_value, Global::MAX_DB_CUT, Global::MAX_DB_BOOST, bounds_bottom, bounds_y);

    getLookAndFeel().drawLinearSlider(g,
                                      bounds.getX(),
                                      bounds_y,
                                      bounds.getWidth(),
                                      bounds.getHeight(),
                                      val,
                                      bounds_bottom,
                                      bounds_y,
                                      getSliderStyle(),
                                      *this);
}

/*---------------------------------------------------------------------------
**
*/
void
EqBandSlider::parameterValueChanged(int parameter_index, float new_value)
{
    juce::ignoreUnused(parameter_index, new_value);

    repaint();
}

/*---------------------------------------------------------------------------
**
*/
void
EqBandSlider::parameterGestureChanged(int parameter_index, bool gesture_is_starting)
{
    // Only implemented because it's pure virtual.
    juce::ignoreUnused(parameter_index, gesture_is_starting);
}

/*---------------------------------------------------------------------------
** End of File
*/
