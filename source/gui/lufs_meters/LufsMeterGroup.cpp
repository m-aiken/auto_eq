#include "LufsMeterGroup.h"

/*---------------------------------------------------------------------------
**
*/
LufsMeterGroup::LufsMeterGroup(PluginProcessor& p)
{
    initMeter(p, Global::Meters::METER_TYPE::SHORT_TERM);
    initMeter(p, Global::Meters::METER_TYPE::MOMENTARY);
    initMeter(p, Global::Meters::METER_TYPE::SHORT_TERM_MAX);
    initMeter(p, Global::Meters::METER_TYPE::MOMENTARY_MAX);
    initMeter(p, Global::Meters::METER_TYPE::INTEGRATED);

    for (auto& meter : meters_) {
        addAndMakeVisible(meter.get());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
LufsMeterGroup::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Track(Fr(100));

    grid.templateRows = {
        Track(Fr(20)),  //
        Track(Fr(20)),  //
        Track(Fr(20)),  //
        Track(Fr(20)),  //
        Track(Fr(20)),  //
    };

    for (auto& meter : meters_) {
        grid.items.add(juce::GridItem(meter.get()));
    }

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
LufsMeterGroup::initMeter(PluginProcessor& p, Global::Meters::METER_TYPE meter_type)
{
    meters_.at(meter_type) = std::make_unique< MonoMeter >(p, meter_type, Global::Meters::ORIENTATION::HORIZONTAL, 40.0);
}

/*---------------------------------------------------------------------------
** End of File
*/
