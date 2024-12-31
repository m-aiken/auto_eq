#include "Theme.h"
#include "ToolbarSeparator.h"

/*---------------------------------------------------------------------------
**
*/
void
ToolbarSeparator::paint(juce::Graphics& g)
{
    const auto bounds = getLocalBounds().toFloat();
    const auto line   = bounds.withSizeKeepingCentre(bounds.getWidth() * 0.2f, bounds.getHeight() * 0.5f);

    g.setColour(Theme::getColour(isEnabled() ? Theme::TOOLBAR_SEPARATOR : Theme::DISABLED_WIDGET));
    g.fillRoundedRectangle(line, 2.f);
}

/*---------------------------------------------------------------------------
** End of File
*/
