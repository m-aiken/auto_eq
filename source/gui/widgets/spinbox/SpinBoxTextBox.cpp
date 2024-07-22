#include "SpinBoxTextBox.h"
#include "../../look_and_feel/Theme.h"
#include "../../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
SpinBoxTextBox::SpinBoxTextBox()
    : juce::Label()
{
    setFont(Theme::getFont());
    setText("0.0", juce::dontSendNotification);
}

/*---------------------------------------------------------------------------
**
*/
void
SpinBoxTextBox::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::yellow);
    g.drawRect(getLocalBounds());
#endif

    g.fillAll(Theme::getColour(Theme::FFT));
    g.setColour(Theme::getColour(Theme::TEXT));
    g.drawFittedText(getText(), getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
