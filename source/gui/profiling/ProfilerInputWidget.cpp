#include "GlobalConstants.h"
#include "ProfilerInputWidget.h"

/*---------------------------------------------------------------------------
**
*/
ProfilerInputWidget::ProfilerInputWidget(PluginProcessor& p)
    : meter_(p)
{
    addAndMakeVisible(meter_);
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
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Track(Fr(100));

    grid.templateRows = {
        // Track(Fr(10)),  //! Label.
        Track(Fr(100)),  //! Meter.
        // Track(Fr(20)),  //! Input trim rotary control.
    };

    // grid.items.add(juce::GridItem());
    grid.items.add(juce::GridItem(meter_));
    // grid.items.add(juce::GridItem());

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
