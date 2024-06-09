#include "MeterGroup.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
MeterGroup::MeterGroup(PluginProcessor& p)
    : peak_label_("PEAK")
    , rms_label_("RMS")
    , lufs_label_("LUFS")
    , peak_meters_(p, Global::PEAK_METER)
    , rms_meters_(p, Global::RMS_METER)
    , lufs_meters_(p, Global::LUFS_METER)
{
    addAndMakeVisible(peak_label_);
    addAndMakeVisible(rms_label_);
    addAndMakeVisible(lufs_label_);

    addAndMakeVisible(peak_meters_);
    addAndMakeVisible(rms_meters_);
    addAndMakeVisible(lufs_meters_);
}

/*---------------------------------------------------------------------------
**
*/
void
MeterGroup::paint(juce::Graphics& g)
{
    if (Global::SHOW_DEBUG_BOUNDS) {
        g.setColour(juce::Colours::red);
        g.drawRect(getLocalBounds());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
MeterGroup::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    using Px    = juce::Grid::Px;

    juce::Grid grid;

    grid.templateColumns = {
        Track(Fr(90)),
        Track(Fr(10)),
    };

    grid.templateRows = {
        Track(Fr(1)),
        Track(Fr(1)),
        Track(Fr(1)),
    };

    grid.items.add(juce::GridItem(peak_meters_));
    grid.items.add(juce::GridItem(peak_label_));

    grid.items.add(juce::GridItem(rms_meters_));
    grid.items.add(juce::GridItem(rms_label_));

    grid.items.add(juce::GridItem(lufs_meters_));
    grid.items.add(juce::GridItem(lufs_label_));

    //    grid.setGap(Px { 4 });
    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
