#include "DecibelMarkers.h"
#include "GlobalConstants.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
DecibelMarkers::DecibelMarkers()
    : min_value_(static_cast< int >(Global::MAX_DB_CUT))
    , max_value_(static_cast< int >(Global::MAX_DB_BOOST))
    , db_interval_(6)
{
}

/*---------------------------------------------------------------------------
**
*/
void
DecibelMarkers::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::green);
    g.drawRect(getLocalBounds());
#endif

    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));

    const juce::Rectangle< int > bounds = getLocalBounds();

    const int offset_top = bounds.getY() + Global::GRAPH_TOP_PADDING;
    const int width      = bounds.getWidth() - X_PADDING;
    const int height     = bounds.getHeight() - Global::GRAPH_TOP_PADDING;

    const int text_height = static_cast< int >(std::floor(Theme::getFont().getHeight()));

    for (int db = min_value_; db <= max_value_; db += db_interval_) {
        const int          y_coord = juce::jmap< int >(db, min_value_, max_value_, height, 0);
        const int          text_y  = y_coord + offset_top - text_height - Y_PADDING;
        const juce::String label   = juce::String(db) + "dB";

        g.drawFittedText((db > 0 ? "+" + label : label),
                         X_PADDING,
                         text_y,
                         width,
                         text_height,
                         juce::Justification::centredLeft,
                         1);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
