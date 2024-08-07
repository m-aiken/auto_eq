#include "GlobalConstants.h"
#include "MeterDbScale.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MeterDbScale::MeterDbScale()
    : min_value_(static_cast< int >(Global::METER_NEG_INF))
    , max_value_(static_cast< int >(Global::METER_MAX_DB))
    , db_interval_(6)
{
}

/*---------------------------------------------------------------------------
**
*/
void
MeterDbScale::paint(juce::Graphics& g)
{
    juce::Rectangle< int > bounds        = getLocalBounds();
    int                    bounds_height = bounds.getHeight();
    int                    padded_width  = bounds.getWidth() - (Global::METER_X_PADDING * 2);
    int                    label_width   = 40;

    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));

    for (int db = min_value_; db <= max_value_; db += db_interval_) {
        int          x_coord  = juce::jmap< int >(db, min_value_, max_value_, 0, padded_width);
        int          offset_x = x_coord + Global::METER_X_PADDING - static_cast< int >(std::floor(label_width * 0.5));
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
