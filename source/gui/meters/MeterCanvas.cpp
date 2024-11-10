#include "GlobalConstants.h"
#include "MeterCanvas.h"
#include "Theme.h"

/*static*/ const uint8 MeterCanvas::DB_INTERVAL = 3;

/*---------------------------------------------------------------------------
**
*/
void
MeterCanvas::paint(juce::Graphics& g)
{
    const auto bounds         = getLocalBounds();
    const auto bounds_width   = bounds.getWidth();
    const auto bounds_height  = bounds.getHeight();
    const int  min_db         = static_cast< int >(Global::METER_NEG_INF);
    const int  max_db         = static_cast< int >(Global::METER_MAX_DB);
    const auto line_colour    = Theme::getColour(Theme::ANALYSER_GRID);
    const auto alpha          = Theme::dark_mode ? 0.05f : 0.1f;
    const int  line_thickness = 1;

    g.setColour(line_colour.withAlpha(alpha));

    // dB markers (vertical - the meters are horizontal).
    for (int i = min_db; i <= max_db; i += DB_INTERVAL) {
        int x = juce::roundToInt(juce::jmap< float >(i, min_db, max_db, 0, bounds_width));

        if (i == max_db) {
            // The final line needs to be pulled left by the thickness of the line.
            // Otherwise it would go out of the bounding box of this widget.
            x -= line_thickness;
        }

        g.fillRect(x, 0, line_thickness, bounds_height);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
