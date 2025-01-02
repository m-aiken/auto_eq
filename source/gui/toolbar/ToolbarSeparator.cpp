#include "Theme.h"
#include "ToolbarSeparator.h"

/*---------------------------------------------------------------------------
**
*/
void
ToolbarSeparator::paint(juce::Graphics& g)
{
    const auto bounds = getLocalBounds().toFloat();
    const auto line   = bounds.withSizeKeepingCentre(bounds.getWidth() * 0.2f, bounds.getHeight() * 0.2f);

    g.setColour(Theme::getColour(Theme::TOOLBAR_SEPARATOR));
    g.fillRoundedRectangle(line, 2.f);
}

/*---------------------------------------------------------------------------
** End of File
*/
