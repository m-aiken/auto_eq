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
    auto        bounds  = getLocalBounds();
    const uint8 padding = Global::ANALYSER_PADDING;

    db_scale_.setBounds(juce::Rectangle< int >(0, 0, padding, bounds.getHeight()));
    hz_scale_.setBounds(juce::Rectangle< int >(padding, 0, bounds.getWidth() - (padding * 2), padding));

    auto padded_bounds = bounds.reduced(padding);

    backdrop_.setBounds(padded_bounds);
    response_curve_.setBounds(padded_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
