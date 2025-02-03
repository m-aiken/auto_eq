#include "EqIntensity.h"
#include "GlobalConstants.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
EqIntensity::EqIntensity(juce::AudioProcessorValueTreeState& apvts)
    : widget_label_("eq_intensity_widget_label", "EQ Intensity")
    , rotary_control_(apvts, GuiParams::EQ_INTENSITY)
    , off_label_("eq_intensity_off_label", "Off", juce::Justification::centredLeft)
    , full_label_("eq_intensity_full_label", "100%", juce::Justification::centredRight)
{
    addAndMakeVisible(widget_label_);
    addAndMakeVisible(rotary_control_);
    addAndMakeVisible(off_label_);
    addAndMakeVisible(full_label_);
}

/*---------------------------------------------------------------------------
**
*/
void
EqIntensity::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::yellow);
    g.drawRect(getLocalBounds());
#endif

    g.setColour(Theme::getColour(Theme::SECTION_BORDER));
    g.drawRect(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
EqIntensity::resized()
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
    grid.items.add(juce::GridItem());

    const juce::Rectangle< int > og_bounds     = getLocalBounds();
    const juce::Rectangle< int > padded_bounds = og_bounds.withSizeKeepingCentre(og_bounds.getWidth() - (PADDING * 2),
                                                                                 og_bounds.getHeight() - (PADDING * 2));

    grid.performLayout(padded_bounds);

    const int rotary_control_bottom = rotary_control_.getBottom();
    const int center_x              = padded_bounds.getCentreX();
    const int label_width           = static_cast< int >(std::floor(padded_bounds.getWidth() * 0.3));
    const int label_height          = static_cast< int >(std::floor(padded_bounds.getHeight() * 0.15));

    off_label_.setBounds(center_x - label_width, rotary_control_bottom, label_width, label_height);
    full_label_.setBounds(center_x, rotary_control_bottom, label_width, label_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
