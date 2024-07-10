#include "FilterMagnitudesCalculator.h"
#include "../../dsp/Equalizer.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
FilterMagnitudesCalculator::FilterMagnitudesCalculator(PluginProcessor& processor_ref)
    : juce::Thread("THREAD_filter_magnitudes_calculator")
    , fifo_write_idx_(1)
    , fifo_read_idx_(0)
    , processor_ref_(processor_ref)
    , num_x_pixels_(0)
{
}

/*---------------------------------------------------------------------------
**
*/
FilterMagnitudesCalculator::~FilterMagnitudesCalculator()
{
    stopThread(Global::BAND_MAGNITUDE_CALCULATION_FREQUENCY_MS);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterMagnitudesCalculator::prepare(uint16 num_x_pixels)
{
    num_x_pixels_ = num_x_pixels;

    resetMagnitudesVectors();
    startThread();
}

/*---------------------------------------------------------------------------
**
*/
void
FilterMagnitudesCalculator::run()
{
    while (!threadShouldExit()) {
        calculateMagnitudes();

        if (++fifo_write_idx_ == FIFO_SIZE) {
            fifo_write_idx_ = 0;
        }

        if (++fifo_read_idx_ == FIFO_SIZE) {
            fifo_read_idx_ = 0;
        }

        wait(Global::BAND_MAGNITUDE_CALCULATION_FREQUENCY_MS);
    }
}

/*---------------------------------------------------------------------------
**
*/
FilterMagnitudesCalculator::MagnitudesVector&
FilterMagnitudesCalculator::getMagnitudes()
{
    return fifo_.at(fifo_read_idx_);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterMagnitudesCalculator::resetMagnitudesVectors()
{
    for (size_t i = 0; i < FIFO_SIZE; ++i) {
        resetMagnitudesVector(i);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
FilterMagnitudesCalculator::resetMagnitudesVector(size_t index)
{
    MagnitudesVector& mags_vec = fifo_.at(index);

    if (mags_vec.size() != num_x_pixels_) {
        mags_vec.resize(num_x_pixels_);
    }

    std::fill(mags_vec.begin(), mags_vec.end(), 0.0);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterMagnitudesCalculator::calculateMagnitudes()
{
    // Reset the magnitudes vector.
    resetMagnitudesVector(fifo_write_idx_);
    MagnitudesVector& mags_vec = fifo_.at(fifo_write_idx_);

    // Get the filters.
    Equalizer::MonoChain& filter_chain = processor_ref_.getFilterChain();

    double sample_rate = processor_ref_.getSampleRate();

    // Calculate the magnitudes.
    for (size_t i = 0; i < num_x_pixels_; ++i) {
        double mag = 1.0;

        // Get the frequency that this x coordinate represents in the analyser.
        double x_hz = juce::mapToLog10< double >((static_cast< double >(i) / static_cast< double >(num_x_pixels_)),
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

        mags_vec.at(i) = juce::Decibels::gainToDecibels< double >(mag, Global::MAX_DB_CUT);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
