#include "MeterGroup.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
MeterGroup::MeterGroup(PluginProcessor& p)
    : db_scale_()
    , peak_label_("PEAK")
    , rms_label_("RMS")
    , lufs_label_("LUFS")
    , peak_meter_l_([&]() { return p.getMeterValue(Global::PEAK_METER, Global::Channels::PRIMARY_LEFT); })
    , peak_meter_r_([&]() { return p.getMeterValue(Global::PEAK_METER, Global::Channels::PRIMARY_RIGHT); })
    , rms_meter_l_([&]() { return p.getMeterValue(Global::RMS_METER, Global::Channels::PRIMARY_LEFT); })
    , rms_meter_r_([&]() { return p.getMeterValue(Global::RMS_METER, Global::Channels::PRIMARY_RIGHT); })
    , lufs_meter_l_([&]() { return p.getMeterValue(Global::LUFS_METER, Global::Channels::PRIMARY_LEFT); })
    , lufs_meter_r_([&]() { return p.getMeterValue(Global::LUFS_METER, Global::Channels::PRIMARY_RIGHT); })
{
    addAndMakeVisible(db_scale_);

    addAndMakeVisible(peak_label_);
    addAndMakeVisible(rms_label_);
    addAndMakeVisible(lufs_label_);

    addAndMakeVisible(peak_meter_l_);
    addAndMakeVisible(peak_meter_r_);
    addAndMakeVisible(rms_meter_l_);
    addAndMakeVisible(rms_meter_r_);
    addAndMakeVisible(lufs_meter_l_);
    addAndMakeVisible(lufs_meter_r_);
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

    auto bounds        = getLocalBounds();
    auto bounds_width  = bounds.getWidth();
    auto bounds_height = bounds.getHeight();

    int meter_section_width = static_cast< int >(std::floor(bounds_width * 0.8));
    int label_section_width = static_cast< int >(std::floor(bounds_width * 0.2));

    db_scale_.setBounds(0, 0, meter_section_width, Global::ANALYSER_PADDING);

    juce::Rectangle< int > meter_section(Global::ANALYSER_PADDING,
                                         Global::ANALYSER_PADDING,
                                         meter_section_width - (Global::ANALYSER_PADDING * 2),
                                         bounds_height - Global::ANALYSER_PADDING);

    juce::Rectangle< int > label_section(meter_section_width,
                                         Global::ANALYSER_PADDING,
                                         label_section_width,
                                         bounds_height - Global::ANALYSER_PADDING);

    // Meter Grid.
    juce::Grid meter_grid;

    const uint8 meter_fr   = 6;
    const uint8 padding_fr = 10;

    meter_grid.templateColumns = {
        Track(Fr(1)),
    };

    meter_grid.templateRows = {
        Track(Fr(padding_fr)),
        Track(Fr(meter_fr)),
        Track(Fr(meter_fr)),
        Track(Fr(padding_fr)),
        //
        Track(Fr(padding_fr)),
        Track(Fr(meter_fr)),
        Track(Fr(meter_fr)),
        Track(Fr(padding_fr)),
        //
        Track(Fr(padding_fr)),
        Track(Fr(meter_fr)),
        Track(Fr(meter_fr)),
        Track(Fr(padding_fr)),
    };

    meter_grid.items.add(juce::GridItem());
    meter_grid.items.add(juce::GridItem(peak_meter_l_));
    meter_grid.items.add(juce::GridItem(peak_meter_r_));
    meter_grid.items.add(juce::GridItem());

    meter_grid.items.add(juce::GridItem());
    meter_grid.items.add(juce::GridItem(rms_meter_l_));
    meter_grid.items.add(juce::GridItem(rms_meter_r_));
    meter_grid.items.add(juce::GridItem());

    meter_grid.items.add(juce::GridItem());
    meter_grid.items.add(juce::GridItem(lufs_meter_l_));
    meter_grid.items.add(juce::GridItem(lufs_meter_r_));
    meter_grid.items.add(juce::GridItem());

    meter_grid.setGap(Px { 4 });
    meter_grid.performLayout(meter_section);

    // Label Grid.
    juce::Grid label_grid;

    label_grid.templateColumns = {
        Track(Fr(1)),
    };

    label_grid.templateRows = {
        Track(Fr(1)),
        Track(Fr(1)),
        Track(Fr(1)),
    };

    label_grid.items.add(juce::GridItem(peak_label_));
    label_grid.items.add(juce::GridItem(rms_label_));
    label_grid.items.add(juce::GridItem(lufs_label_));

    label_grid.performLayout(label_section);
}

/*---------------------------------------------------------------------------
** End of File
*/
