#include "GlobalConstants.h"
#include "MeterCanvas.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MeterCanvas::MeterCanvas(const Global::Meters::ORIENTATION meter_orientation)
    : meter_orientation_(meter_orientation)
{
}

/*---------------------------------------------------------------------------
**
*/
void
MeterCanvas::paint(juce::Graphics& g)
{
    const auto bounds        = getLocalBounds();
    const auto bounds_width  = bounds.getWidth();
    const auto bounds_height = bounds.getHeight();
    const int  min_db        = static_cast< int >(Global::METER_NEG_INF);
    const int  max_db        = static_cast< int >(Global::METER_MAX_DB);
    const auto line_colour   = Theme::getColour(Theme::ANALYSER_GRID);
    const auto alpha         = Theme::app_is_in_dark_mode ? 0.05f : 0.1f;

    g.setColour(line_colour.withAlpha(alpha));

    for (int i = min_db; i <= max_db; i += DB_INTERVAL) {
        if (meter_orientation_ == Global::Meters::HORIZONTAL) {
            int x = juce::roundToInt(juce::jmap< float >(i, min_db, max_db, 0, bounds_width));

            if (i == max_db) {
                // The final line needs to be pulled in by the thickness of the line.
                // Otherwise it would go out of the bounding box of this widget.
                x -= LINE_THICKNESS;
            }

            g.fillRect(x, 0, LINE_THICKNESS, bounds_height);
        }
        else {
            int y = juce::roundToInt(juce::jmap< float >(i, min_db, max_db, 0, bounds_height));

            if (i == max_db) {
                // The final line needs to be pulled in by the thickness of the line.
                // Otherwise it would go out of the bounding box of this widget.
                y -= LINE_THICKNESS;
            }

            g.fillRect(0, y, bounds_width, LINE_THICKNESS);
        }
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
