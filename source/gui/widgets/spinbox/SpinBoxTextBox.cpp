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

    // Background.
    g.fillAll(Theme::getColour(isEnabled() ? Theme::UNITY_GAIN_VALUE_BOX : Theme::DISABLED_WIDGET));

    // Value.
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));
    g.setFont(Theme::getFont());
    g.drawFittedText(getText(), getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
