#include "TransportGroup.h"

/*---------------------------------------------------------------------------
**
*/
TransportGroup::TransportGroup(juce::AudioProcessorValueTreeState& apvts)
    : label_("analysis_state_button", "Analyse Input")
    , button_(apvts, GuiParams::ANALYSE_INPUT)
{
    addAndMakeVisible(label_);
    addAndMakeVisible(button_);

    setAlwaysOnTop(true);
}

/*---------------------------------------------------------------------------
**
*/
void
TransportGroup::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoRows = Track(Fr(100));

    grid.templateColumns = {
        Track(Fr(70)),  //! Label.
        Track(Fr(30)),  //! Button.
    };

    grid.items.add(juce::GridItem(label_));
    grid.items.add(juce::GridItem(button_));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
TransportButton&
TransportGroup::getButton()
{
    return button_;
}

/*---------------------------------------------------------------------------
** End of File
*/
