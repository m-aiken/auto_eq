#include "FilterResponseCurve.h"
#include "../Theme.h"

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
    if (magnitudes_.size() == 0) {
        return;
    }

    juce::Path path;

    path.startNewSubPath(0, getYCoordinateFromMagnitude(magnitudes_.front()));

    for (size_t i = 1; i < magnitudes_.size(); ++i) {
        path.lineTo(i, getYCoordinateFromMagnitude(magnitudes_.at(i)));
    }

    g.setColour(Theme::getColour(Theme::TEXT));
    g.strokePath(path, juce::PathStrokeType(1.f));
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
        repaint();
    }
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::addApvtsListeners()
{
    juce::AudioProcessorValueTreeState& apvts = processor_ref_.getApvts();

    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_SLOPE))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_ENABLED))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_SLOPE))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_ENABLED))->addListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::removeApvtsListeners()
{
    juce::AudioProcessorValueTreeState& apvts = processor_ref_.getApvts();

    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_SLOPE))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_ENABLED))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_SLOPE))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_ENABLED))->removeListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::resetMagnitudesVector()
{
    auto num_x_pixels = getLocalBounds().getWidth();

    if (magnitudes_.size() != static_cast< size_t >(num_x_pixels)) {
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
    FilterFactory::MonoChain& filter_chain = processor_ref_.getFilterChain();

    auto& lc = filter_chain.get< FilterFactory::LOW_CUT >();
    auto& ls = filter_chain.get< FilterFactory::LOW_SHELF >();
    auto& p1 = filter_chain.get< FilterFactory::PEAK_1 >();
    auto& p2 = filter_chain.get< FilterFactory::PEAK_2 >();
    auto& p3 = filter_chain.get< FilterFactory::PEAK_3 >();
    auto& p4 = filter_chain.get< FilterFactory::PEAK_4 >();
    auto& p5 = filter_chain.get< FilterFactory::PEAK_5 >();
    auto& hs = filter_chain.get< FilterFactory::HIGH_SHELF >();
    auto& hc = filter_chain.get< FilterFactory::HIGH_CUT >();

    // Calculate the magnitudes.
    auto   num_x_pixels = getLocalBounds().getWidth();
    double sample_rate  = processor_ref_.getSampleRate();

    for (auto i = 0; i < num_x_pixels; ++i) {
        double mag = 1.0;

        // Get the frequency that this x coordinate represents in the analyser.
        double x_hz = juce::mapToLog10< double >((static_cast< double >(i) / static_cast< double >(num_x_pixels)),
                                                 Global::MIN_HZ,
                                                 Global::MAX_HZ);

        // Low Cut.
        mag *= lc.get< FilterFactory::SLOPE_12 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= lc.get< FilterFactory::SLOPE_24 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= lc.get< FilterFactory::SLOPE_36 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= lc.get< FilterFactory::SLOPE_48 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);

        // Low Shelf.
        mag *= ls.coefficients->getMagnitudeForFrequency(x_hz, sample_rate);

        // Peak bands.
        mag *= p1.coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= p2.coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= p3.coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= p4.coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= p5.coefficients->getMagnitudeForFrequency(x_hz, sample_rate);

        // High Shelf.
        mag *= hs.coefficients->getMagnitudeForFrequency(x_hz, sample_rate);

        // High Cut.
        mag *= hc.get< FilterFactory::SLOPE_12 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= hc.get< FilterFactory::SLOPE_24 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= hc.get< FilterFactory::SLOPE_36 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);
        mag *= hc.get< FilterFactory::SLOPE_48 >().coefficients->getMagnitudeForFrequency(x_hz, sample_rate);

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
** End of File
*/
