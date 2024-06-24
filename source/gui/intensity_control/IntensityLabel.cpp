#include "IntensityLabel.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
IntensityLabel::IntensityLabel(const juce::String& text)
    : juce::Label("EQ_INTENSITY_LABEL_" + text, text)
{
    setFont(Theme::getFont());
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

    g.setColour(Theme::getColour(Theme::TEXT));
    g.drawFittedText(getText(), getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
