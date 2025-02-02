#include "FilterResponseCanvas.h"
#include "GlobalConstants.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCanvas::paint(juce::Graphics& g)
{
    const juce::Rectangle< int > bounds = getLocalBounds();

    const int bounds_x      = bounds.getX();
    const int bounds_y      = bounds.getY();
    const int bounds_width  = bounds.getWidth();
    const int bounds_bottom = bounds.getBottom();
    const int min_db        = static_cast< int >(Global::MAX_DB_CUT);
    const int max_db        = static_cast< int >(Global::MAX_DB_BOOST);
    const int min_hz        = static_cast< int >(Global::MIN_HZ);
    const int max_hz        = static_cast< int >(Global::MAX_HZ);

    const juce::Colour line_colour = Theme::getColour(Theme::ANALYSER_GRID);
    const float        alpha_bold  = Theme::app_is_in_dark_mode ? 0.05f : 0.1f;
    const float        alpha_faint = Theme::app_is_in_dark_mode ? 0.02f : 0.05f;

    // dB markers (horizontal).
    g.setColour(line_colour.withAlpha(alpha_bold));

    for (int i = min_db; i <= max_db; i += DB_INTERVAL) {
        const int y = juce::jmap< int >(i, min_db, max_db, bounds_bottom, bounds_y);

        g.fillRect(0, y, bounds_width, 1);
    }

    // Hz markers (vertical).
    for (int i = min_hz; i <= max_hz; ++i) {
        if (shouldDrawFrequency(i)) {
            const auto normalised_freq = juce::mapFromLog10< float >(i, Global::MIN_HZ, Global::MAX_HZ);
            const int x = bounds_x + static_cast< int >(std::floor(static_cast< float >(bounds_width) * normalised_freq));
            const float alpha = shouldBeBold(i) ? alpha_bold : alpha_faint;

            g.setColour(line_colour.withAlpha(alpha));
            g.drawVerticalLine(x, static_cast< float >(bounds_y), static_cast< float >(bounds_bottom));
        }
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ bool
FilterResponseCanvas::shouldDrawFrequency(const int freq)
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
/*static*/ bool
FilterResponseCanvas::shouldBeBold(const int freq)
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
