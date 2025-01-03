#include "GlobalConstants.h"
#include "InputTrim.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
InputTrim::InputTrim(juce::AudioProcessorValueTreeState& apvts)
    : widget_label_("input_trim_widget_label", "Input Trim")
    , rotary_control_(apvts, GuiParams::INPUT_TRIM, true, "dB", 1)
    , min_label_("input_trim_min_label", "-24", juce::Justification::centredLeft)
    , max_label_("input_trim_max_label", "+24", juce::Justification::centredRight)
{
    addAndMakeVisible(widget_label_);
    addAndMakeVisible(rotary_control_);
    addAndMakeVisible(min_label_);
    addAndMakeVisible(max_label_);
}

/*---------------------------------------------------------------------------
**
*/
void
InputTrim::paint(juce::Graphics& g)
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
InputTrim::resized()
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

    constexpr int                padding       = 12;
    const juce::Rectangle< int > og_bounds     = getLocalBounds();
    const juce::Rectangle< int > padded_bounds = og_bounds.withSizeKeepingCentre(og_bounds.getWidth() - (padding * 2),
                                                                                 og_bounds.getHeight() - (padding * 2));

    grid.performLayout(padded_bounds);

    const int rotary_control_bottom = rotary_control_.getBottom();
    const int center_x              = padded_bounds.getCentreX();
    const int label_width           = static_cast< int >(std::floor(padded_bounds.getWidth() * 0.3));
    const int label_height          = static_cast< int >(std::floor(padded_bounds.getHeight() * 0.15));

    min_label_.setBounds(center_x - label_width, rotary_control_bottom, label_width, label_height);
    max_label_.setBounds(center_x, rotary_control_bottom, label_width, label_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
