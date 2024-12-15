#include "EqBandSlider.h"
#include "GlobalConstants.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
EqBandSlider::EqBandSlider(juce::AudioProcessorValueTreeState& apvts, const juce::String& parameter_id)
    : juce::Slider(juce::Slider::LinearVertical, juce::Slider::NoTextBox)
    , band_param_(apvts.getParameter(parameter_id))
    , intensity_param_(apvts.getParameter(GuiParams::getName(GuiParams::EQ_INTENSITY)))
{
    slider_attachment_.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, parameter_id, *this));

    if (band_param_ != nullptr) {
        band_param_->addListener(this);
    }

    setRange(Global::MAX_DB_CUT, Global::MAX_DB_BOOST);
}

/*---------------------------------------------------------------------------
**
*/
EqBandSlider::~EqBandSlider()
{
    if (band_param_ != nullptr) {
        band_param_->removeListener(this);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
EqBandSlider::paint(juce::Graphics& g)
{
    if (band_param_ == nullptr || intensity_param_ == nullptr) {
        return;
    }

    juce::Rectangle< float > bounds        = getLocalBounds().toFloat();
    float                    bounds_y      = bounds.getY();
    float                    bounds_bottom = bounds.getBottom();
    float                    intensity     = intensity_param_->getValue();
    float                    band_value    = band_param_->convertFrom0to1(band_param_->getValue());

    // Display the raw band value (i.e. without the intensity factored in) as a sort of ghost value.
    // Note, this is not the real slider thumb.
    g.setColour(Theme::getColour(isEnabled() ? Theme::GHOST_NODE : Theme::DISABLED_WIDGET));
    g.fillEllipse(getGhostNode(band_value));

    // Now display the real slider thumb. It factors in the intensity value as that accurately reflects
    // boost/attenuation being applied.
    float slider_value = getScaledValue(band_value * intensity);

    getLookAndFeel().drawLinearSlider(g,
                                      bounds.getX(),
                                      bounds_y,
                                      bounds.getWidth(),
                                      bounds.getHeight(),
                                      slider_value,
                                      bounds_bottom,
                                      bounds_y,
                                      getSliderStyle(),
                                      *this);
}

/*---------------------------------------------------------------------------
**
*/
void
EqBandSlider::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(isEnabled() ? juce::MouseCursor::DraggingHandCursor : juce::MouseCursor::NormalCursor);
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
**
*/
float
EqBandSlider::getScaledValue(float raw_value) const
{
    auto bounds = getLocalBounds().toFloat();

    return juce::jmap< float >(raw_value, Global::MAX_DB_CUT, Global::MAX_DB_BOOST, bounds.getBottom(), bounds.getY());
}

/*---------------------------------------------------------------------------
**
*/
juce::Rectangle< float >
EqBandSlider::getGhostNode(float band_value) const
{
    auto  bounds   = getLocalBounds().toFloat();
    float diameter = bounds.getWidth();
    float x        = bounds.getCentreX() - (diameter * 0.5f);
    float y        = getScaledValue(band_value) - (diameter * 0.5f);

    return juce::Rectangle< float >(x, y, diameter, diameter);
}

/*---------------------------------------------------------------------------
** End of File
*/
