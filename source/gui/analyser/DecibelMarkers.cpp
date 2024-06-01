#include "DecibelMarkers.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*static*/ const uint8 DecibelMarkers::DB_INTERVAL = 6;

/*---------------------------------------------------------------------------
**
*/
DecibelMarkers::DecibelMarkers()
    : font_(Global::ANALYSER_MARKER_FONT_SIZE, juce::Font::bold)
{
}

/*---------------------------------------------------------------------------
**
*/
void
DecibelMarkers::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();

    int x      = bounds.getX();
    int y      = bounds.getY() + Global::ANALYSER_PADDING;
    int width  = bounds.getWidth();
    int height = bounds.getHeight() - (Global::ANALYSER_PADDING * 2);

    float text_height = g.getCurrentFont().getHeight();

    const int min_db = static_cast< int >(Global::NEG_INF);
    const int max_db = static_cast< int >(Global::MAX_DB);

    g.setFont(font_);
    g.setColour(Theme::getColour(Theme::TEXT));

    for (int db = min_db; db <= max_db; db += DB_INTERVAL) {
        int          y_coord = juce::jmap< int >(db, min_db, max_db, height, 0);
        int          text_y  = y_coord + y - static_cast< int >(std::floor(text_height * 0.5));
        juce::String label   = juce::String(db) + "dB";

        g.drawFittedText((db > 0 ? "+" + label : label), x, text_y, width, text_height, juce::Justification::centred, 1);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
