#include "StereoMeter.h"
#include "../Theme.h"

/*---------------------------------------------------------------------------
**
*/
StereoMeter::StereoMeter(Global::METER_TYPE meter_type, PluginProcessor& p)
    : meter_l_([&]() { return p.getMeterValue(meter_type, Global::Channels::PRIMARY_LEFT); })
    , meter_r_([&]() { return p.getMeterValue(meter_type, Global::Channels::PRIMARY_RIGHT); })
{
    addAndMakeVisible(meter_l_);
    addAndMakeVisible(db_scale_);
    addAndMakeVisible(meter_r_);
}

/*---------------------------------------------------------------------------
**
*/
void
StereoMeter::resized()
{
    juce::Rectangle< int > bounds         = getLocalBounds();
    int                    meter_height   = bounds.getHeight() - (Global::ANALYSER_PADDING * 2);
    int                    meter_width    = static_cast< int >(std::floor(bounds.getWidth() * 0.2));
    int                    db_scale_width = static_cast< int >(std::floor(bounds.getWidth() * 0.6));

    meter_l_.setBounds(0, Global::ANALYSER_PADDING, meter_width, meter_height);

    db_scale_.setBounds(meter_width, 0, db_scale_width, bounds.getHeight());

    meter_r_.setBounds(bounds.getRight() - meter_width, Global::ANALYSER_PADDING, meter_width, meter_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
