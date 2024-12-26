#include "GlobalConstants.h"
#include "ProfilerInputWidget.h"

/*---------------------------------------------------------------------------
**
*/
ProfilerInputWidget::ProfilerInputWidget(PluginProcessor& p)
    : label_("profiler_input_widget_label", "Input Level")
    , meter_(p)
    , input_trim_(p.getApvts(), GuiParams::INPUT_TRIM)
{
    addAndMakeVisible(label_);
    addAndMakeVisible(meter_);
    addAndMakeVisible(input_trim_);
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
        Track(Fr(10)),  //! Label.
        Track(Fr(70)),  //! Meter.
        Track(Fr(20)),  //! Input trim rotary control.
    };

    grid.items.add(juce::GridItem(label_));
    grid.items.add(juce::GridItem(meter_));
    grid.items.add(juce::GridItem(input_trim_));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
