#include "FilterResponseBands.h"
#include "GlobalConstants.h"
#include "Theme.h"

/*static*/ const uint8 FilterResponseBands::BAR_WIDTH      = 8;
/*static*/ const uint8 FilterResponseBands::HALF_BAR_WIDTH = 4;

/*---------------------------------------------------------------------------
**
*/
FilterResponseBands::FilterResponseBands(PluginProcessor& p)
    : x_coordinates_calculated_(false)
    , magnitudes_calculator_(p)
{
    juce::AudioProcessorValueTreeState& apvts = p.getApvts();

    for (size_t i = 0; i < Equalizer::NUM_BANDS; ++i) {
        juce::String band_str = Equalizer::getBandName(static_cast< Equalizer::BAND_ID >(i));
        sliders_.at(i)        = std::make_unique< EqBandSlider >(apvts, band_str);

        addAndMakeVisible(sliders_.at(i).get());
    }

    // The filter response graph has multiple widgets stacked on the z axis (this being one of them).
    // Make sure this layer is always on the top so that the band sliders are accessible to the user.
    setAlwaysOnTop(true);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseBands::resized()
{
    // Initialise the x coordinates and prepare the magnitudes calculator.
    // We're doing this via the resized method because both need to know the
    // component's bounds, which aren't known in the constructor.
    calculateXCoordinates();
    magnitudes_calculator_.prepare(getLocalBounds().getWidth());

    const int bounds_height = getLocalBounds().getHeight();

    // Note: We're not drawing the sliders for the 20Hz or 20kHz bands.
    for (size_t i = 1; i < Equalizer::NUM_BANDS - 1; ++i) {
        sliders_.at(i)->setBounds(x_coordinates_.at(i), 0, BAR_WIDTH, bounds_height);
    }
}

/*---------------------------------------------------------------------------
**
*/
int
FilterResponseBands::getYCoordinateFromMagnitude(const double magnitude) const
{
    const juce::Rectangle< int > bounds        = getLocalBounds();
    const int                    bounds_top    = bounds.getY();
    const int                    bounds_bottom = bounds.getBottom();

    const auto y = juce::jmap< double >(magnitude, Global::MAX_DB_CUT, Global::MAX_DB_BOOST, bounds_bottom, bounds_top);

    return static_cast< int >(std::floor(y));
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseBands::updateSliderValues()
{
    const FilterMagnitudesCalculator::MagnitudesVector& magnitudes = magnitudes_calculator_.getMagnitudes();

    if (!x_coordinates_calculated_ || magnitudes.empty()) {
        return;
    }

    for (uint8 i = 1; i < Equalizer::NUM_BANDS - 1; ++i) {
        const int    hz           = x_coordinates_.at(i);
        const double slider_value = magnitudes.at(static_cast< size_t >(hz));

        sliders_.at(i)->setValue(slider_value, juce::dontSendNotification);
    }
}

/*---------------------------------------------------------------------------
**
*/
int
FilterResponseBands::getBandBarHeight(const double magnitude) const
{
    const juce::Rectangle< int > bounds      = getLocalBounds();
    const int                    centre_y    = bounds.getCentreY();
    const int                    abs_y_coord = getYCoordinateFromMagnitude(std::abs(magnitude));

    return (centre_y - abs_y_coord);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseBands::calculateXCoordinates()
{
    const juce::Rectangle< int > bounds       = getLocalBounds();
    const int                    bounds_width = bounds.getWidth();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        const float band_hz   = Equalizer::getBandHz(static_cast< Equalizer::BAND_ID >(i));
        const float scaled_hz = juce::mapFromLog10< float >(band_hz, Global::MIN_HZ, Global::MAX_HZ);
        const int   x_raw     = static_cast< int >(std::floor(bounds_width * scaled_hz));
        const int   x         = juce::jmin< int >(x_raw, bounds_width - 1);

        x_coordinates_.at(static_cast< size_t >(i)) = x;
    }

    x_coordinates_calculated_ = true;
}

/*---------------------------------------------------------------------------
** End of File
*/
