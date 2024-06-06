#include "FilterResponseCurve.h"
#include "../Theme.h"
#include "../../dsp/FilterFactory.h"

/*---------------------------------------------------------------------------
**
*/
FilterResponseCurve::FilterResponseCurve(PluginProcessor& p)
    : processor_ref_(p)
    , should_repaint_(false)
{
    addApvtsListeners();
    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
FilterResponseCurve::~FilterResponseCurve()
{
    stopTimer();
    removeApvtsListeners();
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::paint(juce::Graphics& g)
{
    if (path_.isEmpty()) {
        return;
    }

    g.setColour(Theme::getColour(Theme::FILTER_RESPONSE_PATH));
    g.strokePath(path_, juce::PathStrokeType(2.f));
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

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::timerCallback()
{
    if (should_repaint_.compareAndSetBool(false, true)) {
        calculateMagnitudes();
        plotPath();
        repaint();
    }
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
    juce::AudioProcessorValueTreeState& apvts = processor_ref_.getApvts();

    // Reset the magnitudes vector.
    resetMagnitudesVector();

    // Get the filters.
    FilterFactory::MonoChain& filter_chain = processor_ref_.getFilterChain();

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
        mag *= filter_chain.get< FilterFactory::B1 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B2 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B3 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B4 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B5 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B6 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B7 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B8 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B9 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B10 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B11 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B12 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B13 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B14 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B15 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B16 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B17 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B18 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B19 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B20 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B21 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B22 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B23 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B24 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B25 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B26 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B27 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B28 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B29 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B30 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= filter_chain.get< FilterFactory::B31 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);

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

    double y = juce::jmap< double >(magnitude, Global::NEG_INF, Global::MAX_DB, bounds_bottom, bounds_top);

    return static_cast< int >(std::floor(y));
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

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::addApvtsListeners()
{
    juce::AudioProcessorValueTreeState& apvts = processor_ref_.getApvts();

    for (uint8 i = 0; i < FilterFactory::NUM_BANDS; ++i) {
        FilterFactory::Band band_id  = static_cast< FilterFactory::Band >(i);
        juce::String        param_id = FilterFactory::getBandName(band_id);

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

    for (uint8 i = 0; i < FilterFactory::NUM_BANDS; ++i) {
        FilterFactory::Band band_id  = static_cast< FilterFactory::Band >(i);
        juce::String        param_id = FilterFactory::getBandName(band_id);

        apvts.getParameter(param_id)->removeListener(this);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
