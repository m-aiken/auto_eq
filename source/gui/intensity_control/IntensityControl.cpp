#include "IntensityControl.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
IntensityControl::IntensityControl(juce::AudioProcessorValueTreeState& apvts)
    : rotary_(apvts, "EQ_INTENSITY")
{
    addAndMakeVisible(label_);
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
    auto bounds          = getLocalBounds();
    auto bounds_width    = bounds.getWidth();
    auto bounds_height   = bounds.getHeight();
    auto label_height    = bounds_height * 0.1;
    auto rotary_diameter = bounds_height - (label_height * 2);

    label_.setBounds(0, 0, bounds_width, label_height);
    rotary_.setBounds(label_height, label_height, rotary_diameter, rotary_diameter);
}

/*---------------------------------------------------------------------------
** End of File
*/
