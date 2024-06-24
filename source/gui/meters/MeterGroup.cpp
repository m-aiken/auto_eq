#include "MeterGroup.h"

/*---------------------------------------------------------------------------
**
*/
MeterGroup::MeterGroup(PluginProcessor& p)
    : peak_label_("PEAK")
    , rms_label_("RMS")
    , lufs_label_("LUFS")
    , peak_meters_(p, Global::Meters::PEAK_METER)
    , rms_meters_(p, Global::Meters::RMS_METER)
    , lufs_meters_(p, Global::Meters::LUFS_METER)
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
    auto initial_bounds = getLocalBounds();
    auto padding        = 8;
    auto bounds         = juce::Rectangle< int >(padding,
                                         padding,
                                         initial_bounds.getWidth() - (padding * 2),
                                         initial_bounds.getHeight() - (padding * 2));

    grid.performLayout(bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
