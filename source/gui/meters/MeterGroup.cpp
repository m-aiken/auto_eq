#include "MeterGroup.h"

/*---------------------------------------------------------------------------
**
*/
MeterGroup::MeterGroup(PluginProcessor& p)
{
    initMeter(p, Global::Meters::METER_TYPE::INPUT_GAIN);
    initMeter(p, Global::Meters::METER_TYPE::OUTPUT_PEAK);
    initMeter(p, Global::Meters::METER_TYPE::OUTPUT_RMS);
    initMeter(p, Global::Meters::METER_TYPE::MOMENTARY_LOUDNESS);
    initMeter(p, Global::Meters::METER_TYPE::SHORT_TERM_LOUDNESS);

    for (auto& meter : meters_) {
        addAndMakeVisible(meter.get());
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
MeterGroup::initMeter(PluginProcessor& p, Global::Meters::METER_TYPE meter_type)
{
    meters_.at(meter_type) = std::make_unique< MonoMeter >(p, meter_type, Global::Meters::ORIENTATION::HORIZONTAL, 40.0);
}

/*---------------------------------------------------------------------------
** End of File
*/
