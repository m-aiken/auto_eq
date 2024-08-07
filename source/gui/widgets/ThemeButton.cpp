#include "GlobalConstants.h"
#include "Theme.h"
#include "ThemeButton.h"

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
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif

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
