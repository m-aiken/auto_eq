#include "ThemeButton.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

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
    if (Global::SHOW_DEBUG_BOUNDS) {
        g.setColour(juce::Colours::blue);
        g.drawRect(getLocalBounds());
    }

    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(Theme::TEXT));
    g.drawFittedText(Theme::dark_mode ? "LIGHT" : "DARK", getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
ThemeButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);
}

/*---------------------------------------------------------------------------
** End of File
*/
