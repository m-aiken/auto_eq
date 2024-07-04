#include "FilterResponseCanvas.h"
#include "../look_and_feel/Theme.h"
#include "../../dsp/Equalizer.h"
#include "../../utility/GlobalConstants.h"

/*static*/ const uint8 FilterResponseCanvas::DB_INTERVAL = 3;

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCanvas::paint(juce::Graphics& g)
{
    auto      bounds        = getLocalBounds();
    auto      bounds_x      = bounds.getX();
    auto      bounds_y      = bounds.getY();
    auto      bounds_width  = bounds.getWidth();
    auto      bounds_bottom = bounds.getBottom();
    const int min_db        = static_cast< int >(Global::MAX_DB_CUT);
    const int max_db        = static_cast< int >(Global::MAX_DB_BOOST);
    const int min_hz        = static_cast< int >(Global::MIN_HZ);
    const int max_hz        = static_cast< int >(Global::MAX_HZ);
    auto      line_colour   = Theme::getColour(Theme::ANALYSER_GRID);
    auto      alpha_bold    = Theme::dark_mode ? 0.05f : 0.1f;
    auto      alpha_faint   = Theme::dark_mode ? 0.02f : 0.05f;

    // dB markers (horizontal).
    g.setColour(line_colour.withAlpha(alpha_bold));

    for (int i = min_db; i <= max_db; i += DB_INTERVAL) {
        int y = juce::roundToInt(juce::jmap< float >(i, min_db, max_db, bounds_bottom, bounds_y));

        g.fillRect(0, y, bounds_width, 1);
    }

    // Hz markers (vertical).
    for (int i = min_hz; i <= max_hz; ++i) {
        if (shouldDrawFrequency(i)) {
            auto normalised_freq = juce::mapFromLog10< float >(i, min_hz, max_hz);
            auto x               = bounds_x + (bounds_width * normalised_freq);
            auto alpha           = shouldBeBold(i) ? alpha_bold : alpha_faint;

            g.setColour(line_colour.withAlpha(alpha));
            g.drawVerticalLine(x, bounds_y, bounds_bottom);
        }
    }
}

/*---------------------------------------------------------------------------
**
*/
bool
FilterResponseCanvas::shouldDrawFrequency(int freq) const
{
    bool draw = false;

    draw |= (freq <= 50) && (freq % 10 == 0);
    draw |= (freq <= 200) && (freq % 20 == 0);
    draw |= (freq <= 1000) && (freq % 100 == 0);
    draw |= (freq <= 2000) && (freq % 200 == 0);
    draw |= (freq <= 5000) && (freq % 500 == 0);
    draw |= (freq % 1000 == 0);

    return draw;
}

/*---------------------------------------------------------------------------
**
*/
bool
FilterResponseCanvas::shouldBeBold(int freq) const
{
    bool bold = false;

    bold |= (freq == 50);
    bold |= (freq == 100);
    bold |= (freq == 200);
    bold |= (freq == 500);
    bold |= (freq == 1000);
    bold |= (freq == 2000);
    bold |= (freq == 5000);
    bold |= (freq == 10000);

    return bold;
}

/*---------------------------------------------------------------------------
** End of File
*/
