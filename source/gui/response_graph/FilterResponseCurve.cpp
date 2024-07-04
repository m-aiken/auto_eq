#include "FilterResponseCurve.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*static*/ const uint8 FilterResponseCurve::BAR_WIDTH      = 8;
/*static*/ const uint8 FilterResponseCurve::HALF_BAR_WIDTH = 4;

/*---------------------------------------------------------------------------
**
*/
FilterResponseCurve::FilterResponseCurve(PluginProcessor& p)
    : processor_ref_(p)
    , x_coordinates_calculated_(false)
    , should_repaint_(true)
{
    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
FilterResponseCurve::~FilterResponseCurve()
{
    stopTimer();
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::paint(juce::Graphics& g)
{
    if (!x_coordinates_calculated_ || magnitudes_.size() == 0) {
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
        int y          = getYCoordinateFromMagnitude(magnitudes_.at(x));
        int bar_height = getBandBarHeight(magnitudes_.at(x));

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
FilterResponseCurve::resized()
{
    // Initialise the magnitudes vector and x coordinates.
    // We're doing this via the resized method because both need to know the
    // component's bounds, which aren't known in the constructor.
    resetMagnitudesVector();
    calculateXCoordinates();
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::timerCallback()
{
    //    if (should_repaint_.compareAndSetBool(false, true)) {
    calculateMagnitudes();
    repaint();
    //    }
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::resetMagnitudesVector()
{
    size_t num_x_pixels = static_cast< size_t >(getLocalBounds().getWidth());

    if (magnitudes_.size() != num_x_pixels) {
        magnitudes_.resize(num_x_pixels);
    }

    std::fill(magnitudes_.begin(), magnitudes_.end(), 0.0);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::calculateMagnitudes()
{
    // Reset the magnitudes vector.
    resetMagnitudesVector();

    // Get the filters.
    Equalizer::MonoChain& filter_chain = processor_ref_.getFilterChain();

    auto   num_x_pixels = getLocalBounds().getWidth();
    double sample_rate  = processor_ref_.getSampleRate();

    // Calculate the magnitudes.
    for (size_t i = 0; i < num_x_pixels; ++i) {
        double mag = 1.0;

        // Get the frequency that this x coordinate represents in the analyser.
        double x_hz = juce::mapToLog10< double >((static_cast< double >(i) / static_cast< double >(num_x_pixels)),
                                                 Global::MIN_HZ,
                                                 Global::MAX_HZ);

        // Magnitude per band.
        mag *= filter_chain.get< Equalizer::B1 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B2 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B3 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B4 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B5 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B6 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B7 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B8 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B9 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B10 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B11 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B12 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B13 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B14 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B15 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B16 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B17 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B18 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B19 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B20 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B21 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B22 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B23 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B24 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B25 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B26 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B27 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B28 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B29 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B30 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< Equalizer::B31 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);

        magnitudes_.at(i) = juce::Decibels::gainToDecibels< double >(mag, Global::MAX_DB_CUT);
    }
}

/*---------------------------------------------------------------------------
**
*/
int
FilterResponseCurve::getYCoordinateFromMagnitude(double magnitude)
{
    auto bounds        = getLocalBounds();
    auto bounds_top    = bounds.getY();
    auto bounds_bottom = bounds.getBottom();

    double y = juce::jmap< double >(magnitude, Global::MAX_DB_CUT, Global::MAX_DB_BOOST, bounds_bottom, bounds_top);

    return static_cast< int >(std::floor(y));
}

/*---------------------------------------------------------------------------
**
*/
int
FilterResponseCurve::getBandBarHeight(double magnitude)
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
FilterResponseCurve::calculateXCoordinates()
{
    auto bounds       = getLocalBounds();
    auto bounds_width = bounds.getWidth();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        float band_hz   = Equalizer::getBandHz(static_cast< Equalizer::BAND_ID >(i));
        float scaled_hz = juce::mapFromLog10< float >(band_hz, Global::MIN_HZ, Global::MAX_HZ);
        int   x_raw     = static_cast< int >(std::floor(bounds_width * scaled_hz));
        int   x         = juce::jmin< int >(x_raw, magnitudes_.size() - 1);

        x_coordinates_.at(i) = x;
    }

    x_coordinates_calculated_ = true;
}

/*---------------------------------------------------------------------------
** End of File
*/
