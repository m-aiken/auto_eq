#include "DecibelMarkers.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
DecibelMarkers::DecibelMarkers()
    : min_value_(Global::MAX_DB_CUT)
    , max_value_(Global::MAX_DB_BOOST)
    , db_interval_(6)
{
}

/*---------------------------------------------------------------------------
**
*/
void
DecibelMarkers::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();

    int x          = bounds.getX();
    int offset_top = bounds.getY() + Global::ANALYSER_PADDING;
    int width      = bounds.getWidth();
    int height     = bounds.getHeight() - (Global::ANALYSER_PADDING * 2);

    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(Theme::TEXT));

    float text_height = g.getCurrentFont().getHeight();

    for (int db = min_value_; db <= max_value_; db += db_interval_) {
        int          y_coord = juce::jmap< int >(db, min_value_, max_value_, height, 0);
        int          text_y  = y_coord + offset_top - static_cast< int >(text_height);
        juce::String label   = juce::String(db) + "dB";

        g.drawFittedText((db > 0 ? "+" + label : label), x, text_y, width, text_height, juce::Justification::centred, 1);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
