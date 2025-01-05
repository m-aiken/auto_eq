#include "MeterLabelGroup.h"

/*---------------------------------------------------------------------------
**
*/
MeterLabelGroup::MeterLabelGroup()
{
    for (int i = 0; i < labels_.size(); ++i) {
        const juce::String text           = Global::Meters::getName(static_cast< Global::Meters::METER_TYPE >(i));
        const juce::String component_name = "lufs_" + text.toLowerCase() + "_meter_label";

        labels_.at(i) = std::make_unique< DisableableLabel >(component_name, text, juce::Justification::centredRight);

        addAndMakeVisible(labels_.at(i).get());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
MeterLabelGroup::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Track(Fr(100));

    grid.templateRows = {
        Track(Fr(20)), Track(Fr(20)), Track(Fr(20)), Track(Fr(20)), Track(Fr(20)),
    };

    for (auto& label : labels_) {
        grid.items.add(juce::GridItem(label.get()));
    }

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
