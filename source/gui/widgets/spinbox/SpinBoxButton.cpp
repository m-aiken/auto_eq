#include "SpinBoxButton.h"
#include "Theme.h"
#include "GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
SpinBoxButton::SpinBoxButton(bool is_increment)
    : juce::TextButton()
    , is_increment_(is_increment)
{
}

/*---------------------------------------------------------------------------
**
*/
void
SpinBoxButton::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds());
#endif

    // Button background.
    g.fillAll(Theme::getColour(isEnabled() ? Theme::UNITY_GAIN_VALUE_BUTTON : Theme::DISABLED_WIDGET));

    // +/- label.
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));
    g.setFont(Theme::getFont());
    g.drawFittedText(is_increment_ ? "+" : "-", getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
SpinBoxButton::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);
}

/*---------------------------------------------------------------------------
** End of File
*/
