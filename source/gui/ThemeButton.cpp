#include "ThemeButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
ThemeButton::ThemeButton()
{
    setToggleState(Theme::dark_mode, juce::dontSendNotification);

    onClick = [this]() {
        Theme::toggleTheme();
        repaint();
    };
}

/*---------------------------------------------------------------------------
**
*/
void
ThemeButton::paint(juce::Graphics& g)
{
    g.setColour(Theme::getColour(Theme::TEXT));
    g.drawFittedText(Theme::dark_mode ? "LIGHT" : "DARK", getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
