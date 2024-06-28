#include "FftMenu.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
FftMenu::FftMenu(juce::AudioProcessorValueTreeState& apvts)
    : primary_pre_button_(apvts, GuiParams::SHOW_FFT_PRIMARY_PRE_EQ)
    , primary_post_button_(apvts, GuiParams::SHOW_FFT_PRIMARY_POST_EQ)
    , sidechain_button_(apvts, GuiParams::SHOW_FFT_SIDECHAIN)
    , primary_pre_label_("Show Primary Signal Pre EQ")
    , primary_post_label_("Show Primary Signal Post EQ")
    , sidechain_label_("Show Sidechain Signal")
{
    addAndMakeVisible(primary_pre_button_);
    addAndMakeVisible(primary_post_button_);
    addAndMakeVisible(sidechain_button_);

    addAndMakeVisible(primary_pre_label_);
    addAndMakeVisible(primary_post_label_);
    addAndMakeVisible(sidechain_label_);
}

/*---------------------------------------------------------------------------
**
*/
void
FftMenu::paint(juce::Graphics& g)
{
    if (Global::SHOW_DEBUG_BOUNDS) {
        g.setColour(juce::Colours::blue);
        g.drawRect(getLocalBounds());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
FftMenu::resized()
{
    using Tr = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using Px = juce::Grid::Px;

    juce::Grid grid;

    grid.autoRows        = Tr(Fr(1));
    grid.templateColumns = { Tr(Fr(1)), Tr(Fr(8)), Tr(Fr(1)), Tr(Fr(8)), Tr(Fr(1)), Tr(Fr(8)) };

    grid.items.add(juce::GridItem(primary_pre_button_));
    grid.items.add(juce::GridItem(primary_pre_label_));
    grid.items.add(juce::GridItem(primary_post_button_));
    grid.items.add(juce::GridItem(primary_post_label_));
    grid.items.add(juce::GridItem(sidechain_button_));
    grid.items.add(juce::GridItem(sidechain_label_));

    grid.setGap(Px { 4 });
    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
