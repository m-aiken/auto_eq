#include "MeterDbScale.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*static*/ const uint8 MeterDbScale::DB_INTERVAL = 6;

/*---------------------------------------------------------------------------
**
*/
void
MeterDbScale::paint(juce::Graphics& g)
{
    auto bounds        = getLocalBounds();
    int  bounds_height = bounds.getHeight();
    int  padded_width  = bounds.getWidth() - (Global::ANALYSER_PADDING * 2);
    int  label_width   = 40;

    int min_value = static_cast< int >(Global::NEG_INF);
    int max_value = static_cast< int >(Global::MAX_DB);

    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(Theme::TEXT));

    for (int db = min_value; db <= max_value; db += DB_INTERVAL) {
        int          x_coord  = juce::jmap< int >(db, min_value, max_value, 0, padded_width);
        int          offset_x = x_coord + Global::ANALYSER_PADDING - (label_width * 0.5);
        juce::String label    = juce::String(db) + "dB";

        g.drawFittedText((db > 0 ? "+" + label : label),
                         offset_x,
                         0,
                         label_width,
                         bounds_height,
                         juce::Justification::centred,
                         1);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
