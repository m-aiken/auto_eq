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
    , backdrop_(meter_orientation)
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
    const float val           = processor_ref_.getMeterValue(meter_type_);
    const int   scaling_min   = is_horizontal ? 0 : bounds_height;
    const int   scaling_max   = is_horizontal ? bounds_width : 0;
    const auto  scaled_value  = static_cast< int >(std::floor(juce::jmap< float >(val,
                                                                                Global::METER_NEG_INF,
                                                                                Global::METER_MAX_DB,
                                                                                static_cast< float >(scaling_min),
                                                                                static_cast< float >(scaling_max))));

    int meter_thickness = is_horizontal ? bounds_height : bounds_width;
    int x               = 0;             // Default for horizontal meters.
    int y               = scaled_value;  // Default for vertical meters.

    if (meter_width_pct_ != 100.0) {
        meter_thickness = static_cast< int >(std::floor(meter_thickness * (meter_width_pct_ / 100.0)));

        if (is_horizontal) {
            y = static_cast< int >(std::floor(bounds.getCentreY() - (meter_thickness * 0.5)));
        }
        else {
            x = static_cast< int >(std::floor(bounds.getCentreX() - (meter_thickness * 0.5)));
        }
    }

    const int w = is_horizontal ? scaled_value : meter_thickness;
    const int h = is_horizontal ? meter_thickness : (bounds_height - y);

    const juce::Rectangle< int > meter_rect(x, y, w, h);

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
