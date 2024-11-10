#include "MonoMeter.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MonoMeter::MonoMeter(PluginProcessor& p, const Global::Meters::METER_TYPE meter_type, const double meter_width_pct)
    : processor_ref_(p)
    , meter_type_(meter_type)
    , meter_width_pct_(meter_width_pct)
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
    auto  bounds        = getLocalBounds();
    auto  bounds_width  = bounds.getWidth();
    auto  bounds_height = bounds.getHeight();
    float val           = processor_ref_.getMeterValue(meter_type_);
    auto  length        = juce::jmap< float >(val, Global::METER_NEG_INF, Global::METER_MAX_DB, 0, bounds_width);

    uint8 meter_width = bounds_height;
    uint8 y           = 0;

    if (meter_width_pct_ != 100.0) {
        meter_width = static_cast< uint8 >(std::floor(bounds_height * (meter_width_pct_ / 100.0)));
        y           = static_cast< uint8 >(std::floor(bounds.getCentreY() - (meter_width * 0.5)));
    }

    juce::Rectangle< float > meter_rect(0, y, length, meter_width);

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
