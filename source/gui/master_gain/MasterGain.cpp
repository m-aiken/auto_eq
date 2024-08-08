#include "GlobalConstants.h"
#include "MasterGain.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MasterGain::MasterGain()
{
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

    g.setColour(Theme::getColour(Theme::TEXT));
    g.setFont(Theme::getFont());
    g.drawFittedText("Master Gain", getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
MasterGain::resized()
{
}

/*---------------------------------------------------------------------------
** End of File
*/
