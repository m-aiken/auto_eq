#include "MonoMeter.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MonoMeter::MonoMeter(PluginProcessor&                  p,
                     const Global::Meters::METER_TYPE  meter_type,
                     const Global::Meters::ORIENTATION meter_orientation,
                     const double                      meter_width_pct)
    : processor_ref_(p)
    , meter_type_(meter_type)
    , meter_orientation_(meter_orientation)
    , meter_width_pct_(meter_width_pct)
    , backdrop_(Global::Meters::HORIZONTAL)
{
    addAndMakeVisible(backdrop_);

    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
MonoMeter::~MonoMeter()
{
    stopTimer();
}

/*---------------------------------------------------------------------------
**
*/
void
MonoMeter::paint(juce::Graphics& g)
{
    const bool is_horizontal = (meter_orientation_ == Global::Meters::HORIZONTAL);

    const auto  bounds        = getLocalBounds();
    const int   bounds_width  = bounds.getWidth();
    const int   bounds_height = bounds.getHeight();
    const int   max_length    = is_horizontal ? bounds_width : bounds_height;
    const float val           = processor_ref_.getMeterValue(meter_type_);
    const auto  length        = juce::jmap< float >(val, Global::METER_NEG_INF, Global::METER_MAX_DB, 0, max_length);

    uint8 meter_width = is_horizontal ? bounds_height : bounds_width;
    uint8 x           = 0;
    uint8 y           = 0;

    if (meter_width_pct_ != 100.0) {
        meter_width = static_cast< uint8 >(std::floor(meter_width * (meter_width_pct_ / 100.0)));

        if (is_horizontal) {
            y = static_cast< uint8 >(std::floor(bounds.getCentreY() - (meter_width * 0.5)));
        }
        else {
            x = static_cast< uint8 >(std::floor(bounds.getCentreX() - (meter_width * 0.5)));
        }
    }

    const int w = is_horizontal ? length : meter_width;
    const int h = is_horizontal ? meter_width : length;

    juce::Rectangle< float > meter_rect(x, y, w, h);

    g.setColour(Theme::getColour(Theme::METER_VALUE));
    g.fillRect(meter_rect);
}

/*---------------------------------------------------------------------------
**
*/
void
MonoMeter::resized()
{
    backdrop_.setBounds(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
MonoMeter::timerCallback()
{
    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
