#include "IntensityLabel.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
IntensityLabel::IntensityLabel()
    : juce::Label("EQ_INTENSITY_LABEL", "Intensity")
{
}

/*---------------------------------------------------------------------------
**
*/
void
IntensityLabel::paint(juce::Graphics& g)
{
    if (Global::SHOW_DEBUG_BOUNDS) {
        g.setColour(juce::Colours::red);
        g.drawRect(getLocalBounds());
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
