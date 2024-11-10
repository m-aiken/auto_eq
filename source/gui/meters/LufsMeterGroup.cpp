#include "LufsMeterGroup.h"

/*---------------------------------------------------------------------------
**
*/
LufsMeterGroup::LufsMeterGroup(PluginProcessor& p)
{
    using Global::Meters::METER_TYPE;

    const double width_pct = 40.0;

    meters_.at(METER_TYPE::SHORT_TERM)     = std::make_unique< MonoMeter >(p, METER_TYPE::SHORT_TERM, width_pct);
    meters_.at(METER_TYPE::MOMENTARY)      = std::make_unique< MonoMeter >(p, METER_TYPE::MOMENTARY, width_pct);
    meters_.at(METER_TYPE::SHORT_TERM_MAX) = std::make_unique< MonoMeter >(p, METER_TYPE::SHORT_TERM_MAX, width_pct);
    meters_.at(METER_TYPE::MOMENTARY_MAX)  = std::make_unique< MonoMeter >(p, METER_TYPE::MOMENTARY_MAX, width_pct);
    meters_.at(METER_TYPE::INTEGRATED)     = std::make_unique< MonoMeter >(p, METER_TYPE::INTEGRATED, width_pct);

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
        Track(Fr(20)), Track(Fr(20)), Track(Fr(20)), Track(Fr(20)), Track(Fr(20)),
    };

    for (auto& meter : meters_) {
        grid.items.add(juce::GridItem(meter.get()));
    }

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
