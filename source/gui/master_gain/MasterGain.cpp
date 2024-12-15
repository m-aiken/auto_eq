#include "GlobalConstants.h"
#include "MasterGain.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MasterGain::MasterGain(PluginProcessor& p)
    : widget_label_("master_gain_widget_label", "Master Gain")
    , rotary_control_(p.getApvts(), GuiParams::MASTER_GAIN, true, "dB", 1)
    , unity_gain_button_(p.getApvts(), GuiParams::UNITY_GAIN_ENABLED, "Unity Gain", GuiParams::INITIAL_UNITY_GAIN_STATE)
    , processor_ref_(p)
{
    addAndMakeVisible(widget_label_);
    addAndMakeVisible(rotary_control_);
    addAndMakeVisible(unity_gain_button_);

    unity_gain_button_.addListener(this);
}

/*---------------------------------------------------------------------------
**
*/
MasterGain::~MasterGain()
{
    unity_gain_button_.removeListener(this);
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
        Track(Fr(25)),
        Track(Fr(60)),
        Track(Fr(15)),
    };

    grid.items.add(juce::GridItem(widget_label_));
    grid.items.add(juce::GridItem(rotary_control_));
    grid.items.add(juce::GridItem(unity_gain_button_));

    const int              padding       = 12;
    juce::Rectangle< int > og_bounds     = getLocalBounds();
    juce::Rectangle< int > padded_bounds = og_bounds.withSizeKeepingCentre(og_bounds.getWidth() - (padding * 2),
                                                                           og_bounds.getHeight() - (padding * 2));

    grid.performLayout(padded_bounds);
}

/*---------------------------------------------------------------------------
**
*/
void
MasterGain::buttonClicked(juce::Button* button)
{
    if (button != nullptr && button == &unity_gain_button_) {
        bool unity_gain_enabled = unity_gain_button_.getToggleState();

        unity_gain_enabled ? processor_ref_.startUnityGainCalculation() : processor_ref_.stopUnityGainCalculation();
        rotary_control_.setEnabled(!unity_gain_enabled);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
