#include "IntensityControl.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
IntensityControl::IntensityControl(juce::AudioProcessorValueTreeState& apvts)
    : widget_label_("INTENSITY", juce::Justification::centredLeft)
    , min_label_("OFF")
    , max_label_("MAX")
    , rotary_(apvts, GuiParams::getName(GuiParams::EQ_INTENSITY))
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

    g.setColour(Theme::getColour(Theme::SECTION_BORDER));
    g.drawRect(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
IntensityControl::resized()
{
    juce::Rectangle< int > initial_bounds = getLocalBounds();
    juce::uint8            padding        = 16;

    juce::Rectangle< int > bounds(padding,
                                  padding,
                                  initial_bounds.getWidth() - (padding * 2),
                                  initial_bounds.getHeight() - (padding * 2));

    int bounds_width        = bounds.getWidth();
    int bounds_height       = bounds.getHeight();
    int label_height        = static_cast< int >(std::floor(bounds_height * 0.15));
    int rotary_diameter     = static_cast< int >(std::floor(bounds_height - (label_height * 2)));
    int centre_x            = static_cast< int >(std::floor(bounds.getCentreX()));
    int rotary_x            = static_cast< int >(std::floor(centre_x - (rotary_diameter * 0.5)));
    int rotary_y            = static_cast< int >(std::floor(bounds.getCentreY() - (rotary_diameter * 0.5)));
    int min_max_label_y     = static_cast< int >(std::floor(bounds.getBottom() - label_height));
    int min_max_label_width = static_cast< int >(std::floor(bounds_width * 0.4));

    widget_label_.setBounds(bounds.getX(), bounds.getY(), bounds_width, label_height);
    rotary_.setBounds(rotary_x, rotary_y, rotary_diameter, rotary_diameter);
    min_label_.setBounds(centre_x - min_max_label_width, min_max_label_y, min_max_label_width, label_height);
    max_label_.setBounds(centre_x, min_max_label_y, min_max_label_width, label_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
