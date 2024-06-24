#include "FilterResponseCurve.h"
#include "../look_and_feel/Theme.h"
#include "../../dsp/Equalizer.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
FilterResponseCurve::FilterResponseCurve(PluginProcessor& p)
    : processor_ref_(p)
    , should_repaint_(true)
{
    //    addApvtsListeners();
    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
FilterResponseCurve::~FilterResponseCurve()
{
    stopTimer();
    //    removeApvtsListeners();
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::paint(juce::Graphics& g)
{
    if (path_.isEmpty() || magnitudes_.size() == 0) {
        return;
    }

    auto bounds       = getLocalBounds();
    auto bounds_width = bounds.getWidth();
    auto centre_y     = bounds.getCentreY();

    //    g.strokePath(path_, juce::PathStrokeType(2.f));

    // Draw the filter response at each band.
    g.setColour(Theme::getColour(Theme::FILTER_RESPONSE_PATH));

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        float band_hz   = Equalizer::getBandHz(static_cast< Equalizer::BAND_ID >(i));
        float scaled_hz = juce::mapFromLog10< float >(band_hz, Global::MIN_HZ, Global::MAX_HZ);
        int   x_raw     = static_cast< int >(std::floor(bounds_width * scaled_hz));
        int   x         = juce::jmin< int >(x_raw, magnitudes_.size() - 1);
        int   y         = getYCoordinateFromMagnitude(magnitudes_.at(x));

        int bar_width      = 8;
        int half_bar_width = 4;
        int bar_height     = getBandBarHeight(magnitudes_.at(x));

        int left_edge  = (x - half_bar_width);
        int right_edge = (x + half_bar_width);

        if (left_edge < 0) {
            bar_width += left_edge;
            x = 0;
        }
        else if (right_edge > bounds_width) {
            bar_width -= right_edge;
            x = bounds_width - bar_width;
        }

        juce::Rectangle< int > rect(x, juce::jmin< int >(y, centre_y), bar_width, bar_height);
        g.fillRoundedRectangle(rect.toFloat(), 2.f);
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
    // Initialise the magnitudes vector and the subsequent path.
    // We're doing this via the resized method because the vector needs to be
    // initialised to the size of the component bounds width.
    // The bounds aren't known in the constructor.
    resetMagnitudesVector();
    plotPath();
}
#if 0
/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::parameterValueChanged(int parameter_index, float new_value)
{
    juce::ignoreUnused(parameter_index, new_value);

    should_repaint_.set(true);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::parameterGestureChanged(int parameter_index, bool gesture_is_starting)
{
    // Do nothing - only implemented because it's pure virtual.
    juce::ignoreUnused(parameter_index, gesture_is_starting);
}
#endif

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::timerCallback()
{
    //    if (should_repaint_.compareAndSetBool(false, true)) {
    calculateMagnitudes();
    plotPath();
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

        magnitudes_.at(i) = juce::Decibels::gainToDecibels< double >(mag, Global::NEG_INF);
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

    double y = juce::jmap< double >(magnitude,
                                    Equalizer::MAX_BAND_DB_CUT,
                                    Equalizer::MAX_BAND_DB_BOOST,
                                    bounds_bottom,
                                    bounds_top);

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
FilterResponseCurve::plotPath()
{
    if (magnitudes_.size() == 0) {
        return;
    }

    path_.clear();

    path_.startNewSubPath(0, getYCoordinateFromMagnitude(magnitudes_.front()));

    for (size_t i = 1; i < magnitudes_.size(); ++i) {
        path_.lineTo(i, getYCoordinateFromMagnitude(magnitudes_.at(i)));
    }
}
#if 0
/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::addApvtsListeners()
{
    juce::AudioProcessorValueTreeState& apvts = processor_ref_.getApvts();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID band_id  = static_cast< Equalizer::BAND_ID >(i);
        juce::String       param_id = Equalizer::getBandName(band_id);

        apvts.getParameter(param_id)->addListener(this);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::removeApvtsListeners()
{
    juce::AudioProcessorValueTreeState& apvts = processor_ref_.getApvts();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID band_id  = static_cast< Equalizer::BAND_ID >(i);
        juce::String       param_id = Equalizer::getBandName(band_id);

        apvts.getParameter(param_id)->removeListener(this);
    }
}
#endif

/*---------------------------------------------------------------------------
** End of File
*/
