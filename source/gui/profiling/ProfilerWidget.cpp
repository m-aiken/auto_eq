#include "ProfilerWidget.h"

/*---------------------------------------------------------------------------
**
*/
ProfilerWidget::ProfilerWidget(juce::AudioProcessorValueTreeState& apvts, MonoWaveform& mono_waveform_ref)
    : input_widget_(apvts)
    , mono_waveform_ref_(mono_waveform_ref)
{
    addAndMakeVisible(input_widget_);
    addAndMakeVisible(mono_waveform_ref_);
}

/*---------------------------------------------------------------------------
**
*/
void
ProfilerWidget::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
ProfilerWidget::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    // using Px    = juce::Grid::Px;

    juce::Grid grid;

    grid.templateRows = { Track(Fr(10)), Track(Fr(80)), Track(Fr(10)) };

    grid.templateColumns = {
        Track(Fr(10)),  //! Input meter and trim rotary.
        Track(Fr(80)),  //! Waveform.
        Track(Fr(10)),  //! Empty.
    };

    // Row 1.
    grid.items.add(juce::GridItem());
    grid.items.add(juce::GridItem());
    grid.items.add(juce::GridItem());

    // Row 2.
    grid.items.add(juce::GridItem(input_widget_));
    grid.items.add(juce::GridItem(mono_waveform_ref_));
    grid.items.add(juce::GridItem());

    // Row 3.
    grid.items.add(juce::GridItem());
    grid.items.add(juce::GridItem());
    grid.items.add(juce::GridItem());

    // grid.setGap(Px(padding));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
