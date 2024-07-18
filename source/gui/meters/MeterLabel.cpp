#include "MeterLabel.h"
#include "../look_and_feel/Theme.h"

/*---------------------------------------------------------------------------
**
*/
MeterLabel::MeterLabel(const juce::String& text)
    : text_(text)
{
}

/*---------------------------------------------------------------------------
**
*/
void
MeterLabel::paint(juce::Graphics& g)
{
    g.setFont(Theme::getFont().boldened());
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));
    g.drawFittedText(text_, getLocalBounds(), juce::Justification::centred, 1.f);
}

/*---------------------------------------------------------------------------
** End of File
*/
