#include "FilterResponseBands.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*static*/ const uint8 FilterResponseBands::BAR_WIDTH      = 8;
/*static*/ const uint8 FilterResponseBands::HALF_BAR_WIDTH = 4;

/*---------------------------------------------------------------------------
**
*/
FilterResponseBands::FilterResponseBands(PluginProcessor& p)
    : x_coordinates_calculated_(false)
    , magnitudes_calculator_(p)
{
}

/*---------------------------------------------------------------------------
**
*/
FilterResponseBands::~FilterResponseBands()
{
    stopTimer();
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseBands::paint(juce::Graphics& g)
{
    FilterMagnitudesCalculator::MagnitudesVector& magnitudes = magnitudes_calculator_.getMagnitudes();

    if (!x_coordinates_calculated_ || magnitudes.size() == 0) {
        return;
    }

    auto bounds       = getLocalBounds();
    auto bounds_width = bounds.getWidth();
    auto centre_y     = bounds.getCentreY();

    g.setColour(Theme::getColour(Theme::BAND_VALUE));

    // Draw the filter response at each band.
    // Note: We're not drawing the 20Hz or 2kHz bands.
    for (uint8 i = 1; i < Equalizer::NUM_BANDS - 1; ++i) {
        int x          = x_coordinates_.at(i);
        int y          = getYCoordinateFromMagnitude(magnitudes.at(static_cast< size_t >(x)));
        int bar_height = getBandBarHeight(magnitudes.at(static_cast< size_t >(x)));

        // Value sub-rectangle.
        juce::Rectangle< int > val_rect(x - HALF_BAR_WIDTH, juce::jmin< int >(y, centre_y), BAR_WIDTH, bar_height);
        g.fillRoundedRectangle(val_rect.toFloat(), 2.f);
    }

    // Draw a solid line at 0dB across the entire graph.
    g.setColour(Theme::getColour(Theme::GRAPH_0DB_MARKER));
    g.drawRect(0, centre_y - 1, bounds_width, 2);
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

    if (!isTimerRunning()) {
        startTimer(static_cast< int >(Global::BAND_MAGNITUDE_CALCULATION_FREQUENCY_MS));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseBands::timerCallback()
{
    repaint();
}

/*---------------------------------------------------------------------------
**
*/
int
FilterResponseBands::getYCoordinateFromMagnitude(double magnitude)
{
    juce::Rectangle< int > bounds        = getLocalBounds();
    int                    bounds_top    = bounds.getY();
    int                    bounds_bottom = bounds.getBottom();

    double y = juce::jmap< double >(magnitude, Global::MAX_DB_CUT, Global::MAX_DB_BOOST, bounds_bottom, bounds_top);

    return static_cast< int >(std::floor(y));
}

/*---------------------------------------------------------------------------
**
*/
int
FilterResponseBands::getBandBarHeight(double magnitude)
{
    juce::Rectangle< int > bounds      = getLocalBounds();
    int                    centre_y    = bounds.getCentreY();
    int                    abs_y_coord = getYCoordinateFromMagnitude(std::abs(magnitude));

    return (centre_y - abs_y_coord);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseBands::calculateXCoordinates()
{
    juce::Rectangle< int > bounds       = getLocalBounds();
    int                    bounds_width = bounds.getWidth();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        float band_hz   = Equalizer::getBandHz(static_cast< Equalizer::BAND_ID >(i));
        float scaled_hz = juce::mapFromLog10< float >(band_hz, Global::MIN_HZ, Global::MAX_HZ);
        int   x_raw     = static_cast< int >(std::floor(bounds_width * scaled_hz));
        int   x         = juce::jmin< int >(x_raw, bounds_width - 1);

        x_coordinates_.at(static_cast< size_t >(i)) = x;
    }

    x_coordinates_calculated_ = true;
}

/*---------------------------------------------------------------------------
** End of File
*/
