#include "MeterDbScale.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MeterDbScale::MeterDbScale(const Global::Meters::ORIENTATION meter_orientation)
    : meter_orientation_(meter_orientation)
    , min_value_(static_cast< int >(Global::METER_NEG_INF))
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
    const juce::Rectangle< int > bounds        = getLocalBounds();
    const int                    bounds_width  = bounds.getWidth();
    const int                    bounds_height = bounds.getHeight();
    const int                    padded_width  = bounds.getWidth() - (Global::METER_X_PADDING * 2);
    const int                    padded_height = bounds.getHeight() - (Global::METER_Y_PADDING * 2);
    const int                    label_width   = 40;
    const int                    label_height  = 20;

    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));

    for (int db = min_value_; db <= max_value_; db += db_interval_) {
        juce::String label = juce::String(db) + "dB";

        if (db > 0) {
            label = "+" + label;
        }

        if (meter_orientation_ == Global::Meters::HORIZONTAL) {
            const int x_coord  = juce::jmap< int >(db, min_value_, max_value_, 0, padded_width);
            const int offset_x = x_coord + Global::METER_X_PADDING - static_cast< int >(std::floor(label_width * 0.5));

            g.drawFittedText(label, offset_x, 0, label_width, bounds_height, juce::Justification::centred, 1);
        }
        else {
            const int y_coord  = juce::jmap< int >(db, min_value_, max_value_, padded_height, 0);
            const int offset_y = y_coord + Global::METER_Y_PADDING - static_cast< int >(std::floor(label_height * 0.5));

            g.drawFittedText(label, 0, offset_y, bounds_width, label_height, juce::Justification::centred, 1);
        }
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
