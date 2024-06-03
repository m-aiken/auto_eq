#include "MeterLabel.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
MeterLabel::MeterLabel(const juce::String& text)
    : text_(text)
    , font_(Global::ANALYSER_MARKER_FONT_SIZE, juce::Font::bold)
{
}

/*---------------------------------------------------------------------------
**
*/
void
MeterLabel::paint(juce::Graphics& g)
{
    g.setFont(font_);
    g.setColour(Theme::getColour(Theme::TEXT));
    g.drawFittedText(text_, getLocalBounds(), juce::Justification::centred, 1.f);
}

/*---------------------------------------------------------------------------
** End of File
*/
