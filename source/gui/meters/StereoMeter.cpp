#include "StereoMeter.h"

/*---------------------------------------------------------------------------
**
*/
StereoMeter::StereoMeter(PluginProcessor& p, Global::Meters::METER_TYPE meter_type)
    : meter_l_(p, meter_type, Global::Channels::PRIMARY_LEFT)
    , meter_r_(p, meter_type, Global::Channels::PRIMARY_RIGHT)
{
    addAndMakeVisible(db_scale_);
    addAndMakeVisible(meter_l_);
    addAndMakeVisible(meter_r_);
}

/*---------------------------------------------------------------------------
**
*/
void
StereoMeter::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::yellow);
    g.drawRect(getLocalBounds());
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
StereoMeter::resized()
{
    juce::Rectangle< int > bounds = getLocalBounds();

    int bounds_width    = bounds.getWidth();
    int bounds_height   = bounds.getHeight();
    int db_scale_height = static_cast< int >(std::floor(bounds_height * 0.5));
    int meter_height    = static_cast< int >(std::floor(bounds_height * 0.1));
    int meter_width     = static_cast< int >(std::floor(bounds.getWidth() - (Global::ANALYSER_PADDING * 2)));

    db_scale_.setBounds(0, 0, bounds_width, db_scale_height);

    meter_l_.setBounds(Global::ANALYSER_PADDING, bounds.getCentreY(), meter_width, meter_height);
    meter_r_.setBounds(Global::ANALYSER_PADDING, bounds.getBottom() - meter_height, meter_width, meter_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
