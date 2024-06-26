#include "IntensityControl.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
IntensityControl::IntensityControl(juce::AudioProcessorValueTreeState& apvts)
    : widget_label_("INTENSITY", juce::Justification::centredLeft)
    , min_label_("OFF")
    , max_label_("MAX")
    , rotary_(apvts, "EQ_INTENSITY")
{
    addAndMakeVisible(widget_label_);
    addAndMakeVisible(min_label_);
    addAndMakeVisible(max_label_);
    addAndMakeVisible(rotary_);
}

/*---------------------------------------------------------------------------
**
*/
void
IntensityControl::paint(juce::Graphics& g)
{
    if (Global::SHOW_DEBUG_BOUNDS) {
        g.setColour(juce::Colours::lightblue);
        g.drawRect(getLocalBounds());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
IntensityControl::resized()
{
    auto initial_bounds = getLocalBounds();
    auto padding        = 16;
    auto bounds         = juce::Rectangle< int >(padding,
                                         padding,
                                         initial_bounds.getWidth() - (padding * 2),
                                         initial_bounds.getHeight() - (padding * 2));

    auto bounds_width        = bounds.getWidth();
    auto bounds_height       = bounds.getHeight();
    auto label_height        = bounds_height * 0.15;
    auto rotary_diameter     = bounds_height - (label_height * 2);
    auto centre_x            = bounds.getCentreX();
    auto rotary_x            = centre_x - (rotary_diameter * 0.5);
    auto rotary_y            = bounds.getCentreY() - (rotary_diameter * 0.5);
    auto min_max_label_y     = bounds.getBottom() - label_height;
    auto min_max_label_width = bounds_width * 0.4;

    widget_label_.setBounds(bounds.getX(), bounds.getY(), bounds_width, label_height);
    rotary_.setBounds(rotary_x, rotary_y, rotary_diameter, rotary_diameter);
    min_label_.setBounds(centre_x - min_max_label_width, min_max_label_y, min_max_label_width, label_height);
    max_label_.setBounds(centre_x, min_max_label_y, min_max_label_width, label_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
