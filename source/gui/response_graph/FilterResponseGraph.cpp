#include "FilterResponseGraph.h"
#include "../../dsp/FilterFactory.h"

/*---------------------------------------------------------------------------
**
*/
FilterResponseGraph::FilterResponseGraph(PluginProcessor& p)
    : db_scale_(FilterFactory::MAX_BAND_DB_CUT, FilterFactory::MAX_BAND_DB_BOOST, 6)
    , response_curve_(p)
{
    addAndMakeVisible(backdrop_);
    addAndMakeVisible(db_scale_);
    addAndMakeVisible(hz_scale_);
    addAndMakeVisible(response_curve_);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseGraph::resized()
{
    auto                   bounds        = getLocalBounds();
    auto                   bounds_width  = bounds.getWidth();
    auto                   bounds_height = bounds.getHeight();
    const uint8            padding       = Global::ANALYSER_PADDING;
    juce::Rectangle< int > y_padded_bounds(0, padding, bounds_width, bounds_height - (padding * 2));
    juce::Rectangle< int > db_scale_bounds(8, 0, padding, bounds_height);
    juce::Rectangle< int > hz_scale_bounds(0, bounds.getBottom() - padding, bounds_width, padding);

    backdrop_.setBounds(y_padded_bounds);
    response_curve_.setBounds(y_padded_bounds);
    db_scale_.setBounds(db_scale_bounds);
    hz_scale_.setBounds(hz_scale_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
