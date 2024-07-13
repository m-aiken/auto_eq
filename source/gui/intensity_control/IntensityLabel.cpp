#include "IntensityLabel.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
IntensityLabel::IntensityLabel(const juce::String& text, const juce::Justification justification)
    : juce::Label("EQ_INTENSITY_LABEL_" + text, text)
    , justification_(justification)
{
    setFont(Theme::getFont());
}

/*---------------------------------------------------------------------------
**
*/
void
IntensityLabel::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds());
#endif

    g.setColour(Theme::getColour(Theme::TEXT));
    g.drawFittedText(getText(), getLocalBounds(), justification_, 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
