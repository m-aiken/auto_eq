#include "DecibelMarkers.h"
#include "Theme.h"
#include "../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
DecibelMarkers::DecibelMarkers(float min_value, float max_value, uint8 db_interval)
    : font_(Global::ANALYSER_MARKER_FONT_SIZE, juce::Font::bold)
    , min_value_(min_value)
    , max_value_(max_value)
    , db_interval_(db_interval)
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

    g.setFont(font_);
    g.setColour(Theme::getColour(Theme::TEXT));

    for (int db = min_value_; db <= max_value_; db += db_interval_) {
        int          y_coord = juce::jmap< int >(db, min_value_, max_value_, height, 0);
        int          text_y  = y_coord + y - static_cast< int >(std::floor(text_height * 0.5));
        juce::String label   = juce::String(db) + "dB";

        g.drawFittedText((db > 0 ? "+" + label : label), x, text_y, width, text_height, juce::Justification::centred, 1);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
