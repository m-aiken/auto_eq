#include "ModeSelector.h"

/*---------------------------------------------------------------------------
**
*/
ModeSelector::ModeSelector(/*juce::AudioProcessorValueTreeState& apvts*/)
    : analyser_mode_label_("analyser_mode_label", "Analyser")
    , profiler_mode_label_("profiler_mode_label", "Profiler")
{
    addAndMakeVisible(analyser_mode_label_);
    addAndMakeVisible(profiler_mode_label_);
    addAndMakeVisible(toggle_switch_);
}

/*---------------------------------------------------------------------------
**
*/
void
ModeSelector::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoRows = Track(Fr(100));

    grid.templateColumns = {
        Track(Fr(40)),  //! Analyser mode label.
        Track(Fr(20)),  //! Toggle switch.
        Track(Fr(40)),  //! Profiler mode label.
    };

    grid.items.add(juce::GridItem(analyser_mode_label_));
    grid.items.add(juce::GridItem(toggle_switch_));
    grid.items.add(juce::GridItem(profiler_mode_label_));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
ToggleSwitch&
ModeSelector::getToggleSwitch()
{
    return toggle_switch_;
}

/*---------------------------------------------------------------------------
** End of File
*/
