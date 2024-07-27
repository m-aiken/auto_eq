#include "SpinBoxButton.h"
#include "../../look_and_feel/Theme.h"
#include "../../../utility/GlobalConstants.h"

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

    g.fillAll(Theme::getColour(Theme::BAND_VALUE));
    g.setColour(Theme::getColour(Theme::TEXT));
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
