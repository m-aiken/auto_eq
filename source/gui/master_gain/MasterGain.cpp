#include "GlobalConstants.h"
#include "MasterGain.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MasterGain::MasterGain(juce::AudioProcessorValueTreeState& apvts)
    : widget_label_("master_gain_widget_label", "Master Gain", juce::Justification::centredLeft)
    , rotary_control_(apvts, GuiParams::MASTER_GAIN)
    , unity_gain_button_("Unity Gain", apvts, GuiParams::UNITY_GAIN_ENABLED)
{
    addAndMakeVisible(widget_label_);
    addAndMakeVisible(rotary_control_);
    addAndMakeVisible(unity_gain_button_);
}

/*---------------------------------------------------------------------------
**
*/
void
MasterGain::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif

    g.setColour(Theme::getColour(Theme::SECTION_BORDER));
    g.drawRect(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
MasterGain::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Track(Fr(1));

    grid.templateRows = {
        Track(Fr(20)),
        Track(Fr(60)),
        Track(Fr(20)),
    };

    grid.items.add(juce::GridItem(widget_label_));
    grid.items.add(juce::GridItem(rotary_control_));
    grid.items.add(juce::GridItem(unity_gain_button_));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
