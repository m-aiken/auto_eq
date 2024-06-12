#include "MeterCanvas.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*static*/ const uint8 MeterCanvas::DB_INTERVAL = 3;

/*---------------------------------------------------------------------------
**
*/
void
MeterCanvas::paint(juce::Graphics& g)
{
    auto      bounds        = getLocalBounds();
    auto      bounds_width  = bounds.getWidth();
    auto      bounds_height = bounds.getHeight();
    const int min_db        = static_cast< int >(Global::NEG_INF);
    const int max_db        = static_cast< int >(Global::MAX_DB);
    auto      line_colour   = Theme::getColour(Theme::ANALYSER_GRID);
    auto      alpha         = Theme::dark_mode ? 0.1f : 0.2f;

    g.setColour(line_colour.withAlpha(alpha));

    // Draw the outline.
    g.drawRect(bounds);

    // dB markers (vertical - the meters are horizontal).
    for (int i = min_db; i <= max_db; i += DB_INTERVAL) {
        int x = juce::roundToInt(juce::jmap< float >(i, min_db, max_db, 0, bounds_width));

        g.fillRect(x, 0, 1, bounds_height);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
