#include "FrequencyMarkers.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
FrequencyMarkers::FrequencyMarkers()
    : min_hz_(static_cast< int >(Global::MIN_HZ))
    , max_hz_(static_cast< int >(Global::MAX_HZ))
    , label_width_(40)
{
}

/*---------------------------------------------------------------------------
**
*/
void
FrequencyMarkers::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds());
#endif

    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));

    juce::Rectangle< int > bounds = getLocalBounds();

    int bounds_x       = bounds.getX();
    int bounds_width   = bounds.getWidth();
    int bounds_bottom  = bounds.getBottom();
    int label_height   = static_cast< int >(std::floor(Theme::getFont().getHeight()));
    int x_left_padding = 4;
    int y_padding      = 2;
    int y              = bounds_bottom - label_height - y_padding;

    for (int i = min_hz_; i <= max_hz_; ++i) {
        if (shouldDrawFrequency(i)) {
            float        normalised_freq = juce::mapFromLog10< float >(i, min_hz_, max_hz_);
            int          x               = bounds_x + static_cast< int >(std::floor(bounds_width * normalised_freq));
            juce::String label           = (i < 1000.f) ? (juce::String(i) + "Hz") : (juce::String(i / 1000.f) + "kHz");

            g.drawFittedText(label, (x + x_left_padding), y, label_width_, label_height, juce::Justification::centredLeft, 1);
        }
    }
}

/*---------------------------------------------------------------------------
**
*/
bool
FrequencyMarkers::shouldDrawFrequency(int freq) const
{
    bool draw = false;

    draw |= (freq == 50);
    draw |= (freq == 100);
    draw |= (freq == 200);
    draw |= (freq == 500);
    draw |= (freq == 1000);
    draw |= (freq == 2000);
    draw |= (freq == 5000);
    draw |= (freq == 10000);

    return draw;
}

/*---------------------------------------------------------------------------
** End of File
*/
