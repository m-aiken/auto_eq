#include "FrequencyMarkers.h"
#include "GlobalConstants.h"
#include "Theme.h"

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

    const juce::Rectangle< int > bounds = getLocalBounds();

    const int bounds_x      = bounds.getX();
    const int bounds_width  = bounds.getWidth();
    const int bounds_bottom = bounds.getBottom();
    const int label_height  = static_cast< int >(std::floor(Theme::getFont().getHeight()));
    const int y             = bounds_bottom - label_height - Y_PADDING;

    for (int i = min_hz_; i <= max_hz_; ++i) {
        if (shouldDrawFrequency(i)) {
            const auto         normalised_freq = juce::mapFromLog10< float >(i, min_hz_, max_hz_);
            const int          x     = bounds_x + static_cast< int >(std::floor(bounds_width * normalised_freq));
            const juce::String label = (i < 1000.f) ? (juce::String(i) + "Hz") : (juce::String(i / 1000.f) + "kHz");

            g.drawFittedText(label, (x + X_LEFT_PADDING), y, label_width_, label_height, juce::Justification::centredLeft, 1);
        }
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ bool
FrequencyMarkers::shouldDrawFrequency(const int freq)
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
