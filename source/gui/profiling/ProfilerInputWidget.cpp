#include "GlobalConstants.h"
#include "ProfilerInputWidget.h"

/*---------------------------------------------------------------------------
**
*/
ProfilerInputWidget::ProfilerInputWidget(PluginProcessor& p)
    : db_scale_(Global::Meters::VERTICAL)
    , meter_(p)
    , backdrop_(Global::Meters::VERTICAL)
{
    addAndMakeVisible(db_scale_);
    addAndMakeVisible(meter_);
    addAndMakeVisible(backdrop_);
}

/*---------------------------------------------------------------------------
**
*/
void
ProfilerInputWidget::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds());
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
ProfilerInputWidget::resized()
{
    const auto bounds         = getLocalBounds();
    const int  bounds_width   = bounds.getWidth();
    const int  bounds_height  = bounds.getHeight();
    const int  meter_height   = bounds_height - (Global::METER_Y_PADDING * 2);
    const int  db_scale_width = static_cast< int >(std::floor(bounds_width * 0.6));
    const int  meter_width    = static_cast< int >(std::floor(bounds_width * 0.2));

    db_scale_.setBounds(0, 0, db_scale_width, bounds_height);

    meter_.setBounds(db_scale_.getRight(), Global::METER_Y_PADDING, meter_width, meter_height);
    backdrop_.setBounds(db_scale_.getRight(), Global::METER_Y_PADDING, meter_width, meter_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
