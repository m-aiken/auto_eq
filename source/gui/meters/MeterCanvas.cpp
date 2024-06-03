#include "MeterCanvas.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*static*/ const uint8 MeterCanvas::DB_INTERVAL = 3;

/*---------------------------------------------------------------------------
**
*/
MeterCanvas::MeterCanvas()
{
}

/*---------------------------------------------------------------------------
**
*/
void
MeterCanvas::paint(juce::Graphics& g)
{
    auto      bounds        = getLocalBounds();
    auto      bounds_y      = bounds.getY();
    auto      bounds_width  = bounds.getWidth();
    auto      bounds_bottom = bounds.getBottom();
    const int min_db        = static_cast< int >(Global::NEG_INF);
    const int max_db        = static_cast< int >(Global::MAX_DB);
    auto      line_colour   = Theme::getColour(Theme::ANALYSER_GRID);
    auto      alpha         = Theme::dark_mode ? 0.1f : 0.2f;

    g.setColour(line_colour.withAlpha(alpha));

    // Draw the outline.
    g.drawRect(bounds);

    // dB markers (horizontal).
    for (int i = min_db; i <= max_db; i += DB_INTERVAL) {
        int y = juce::roundToInt(juce::jmap< float >(i, min_db, max_db, bounds_bottom, bounds_y));

        g.fillRect(0, y, bounds_width, 1);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
