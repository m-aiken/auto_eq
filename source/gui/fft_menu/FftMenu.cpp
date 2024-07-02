#include "FftMenu.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
FftMenu::FftMenu(juce::AudioProcessorValueTreeState& apvts)
    : primary_pre_button_("Show Primary Signal Pre EQ", apvts, GuiParams::SHOW_FFT_PRIMARY_PRE_EQ)
    , primary_post_button_("Show Primary Signal Post EQ", apvts, GuiParams::SHOW_FFT_PRIMARY_POST_EQ)
    , sidechain_button_("Show Sidechain Signal", apvts, GuiParams::SHOW_FFT_SIDECHAIN)
{
    addAndMakeVisible(primary_pre_button_);
    addAndMakeVisible(primary_post_button_);
    addAndMakeVisible(sidechain_button_);
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
    juce::Rectangle< int > bounds  = getLocalBounds();
    const uint8            padding = 6;
    juce::Rectangle< int > bounds_reduced(padding,
                                          padding,
                                          bounds.getWidth() - (padding * 2),
                                          bounds.getHeight() - (padding * 2));

    using Tr = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoRows        = Tr(Fr(1));
    grid.templateColumns = { Tr(Fr(3)), Tr(Fr(3)), Tr(Fr(3)) };

    grid.items.add(juce::GridItem(primary_pre_button_));
    grid.items.add(juce::GridItem(primary_post_button_));
    grid.items.add(juce::GridItem(sidechain_button_));

    grid.performLayout(bounds_reduced);
}

/*---------------------------------------------------------------------------
** End of File
*/
