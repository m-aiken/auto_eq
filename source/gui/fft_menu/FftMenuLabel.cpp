#include "FftMenuLabel.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
FftMenuLabel::FftMenuLabel(const juce::String& text)
    : juce::Label("FFT_MENU_LABEL_" + text, text)
{
    setFont(Theme::getFont());
}

/*---------------------------------------------------------------------------
**
*/
void
FftMenuLabel::paint(juce::Graphics& g)
{
    if (Global::SHOW_DEBUG_BOUNDS) {
        g.setColour(juce::Colours::red);
        g.drawRect(getLocalBounds());
    }

    g.setColour(Theme::getColour(Theme::TEXT));
    g.drawFittedText(getText(), getLocalBounds(), juce::Justification::centredLeft, 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
