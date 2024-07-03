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
    auto bounds        = getLocalBounds();
    auto bounds_x      = bounds.getX();
    auto bounds_width  = bounds.getWidth();
    auto bounds_height = bounds.getHeight();

    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(Theme::TEXT));

    for (int i = min_hz_; i <= max_hz_; ++i) {
        if (shouldDrawFrequency(i)) {
            auto normalised_freq = juce::mapFromLog10< float >(i, min_hz_, max_hz_);
            auto label_center_x  = bounds_x + (bounds_width * normalised_freq);
            auto label           = (i < 1000.f) ? (juce::String(i) + "Hz") : (juce::String(i / 1000.f) + "kHz");

            g.drawFittedText(label,
                             label_center_x - (label_width_ * 0.5),
                             0,
                             label_width_,
                             bounds_height,
                             juce::Justification::centred,
                             1);
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
