#include "InputAnalysisFft.h"
#include "../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
InputAnalysisFft::InputAnalysisFft(MonoFftBuffer& fft_buffer, juce::AudioProcessorValueTreeState& apvts)
    : fft_(MonoFftBuffer::FFT_ORDER)
    , windowing_fn_(MonoFftBuffer::FFT_SIZE, juce::dsp::WindowingFunction< float >::blackmanHarris)
    , fft_buffer_(fft_buffer)
    , apvts_(apvts)
{
    std::fill(fft_data_.begin(), fft_data_.end(), 0.f);

    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
InputAnalysisFft::~InputAnalysisFft()
{
    stopTimer();
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFft::timerCallback()
{
    DBG("HELLO");
    processFftData();
    updateFilterBands();
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFft::processFftData()
{
    fft_buffer_.getNextBlock(fft_data_);
    windowing_fn_.multiplyWithWindowingTable(fft_data_.data(), MonoFftBuffer::FFT_SIZE);
    fft_.performFrequencyOnlyForwardTransform(fft_data_.data(), true);

    juce::FloatVectorOperations::multiply(fft_data_.data(),
                                          1.f / static_cast< float >(MonoFftBuffer::NUM_BINS),
                                          MonoFftBuffer::NUM_BINS + 1);

    for (size_t i = 0; i < fft_data_.size(); ++i) {
        fft_data_.at(i) = juce::Decibels::gainToDecibels(fft_data_.at(i), Global::NEG_INF);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFft::updateFilterBands()
{
    const size_t num_bins        = MonoFftBuffer::NUM_BINS;
    const float  bin_width       = static_cast< float >(fft_buffer_.getBinWidth());
    const uint8  path_resolution = 2;

    for (size_t i = 1; i < num_bins + 1; i += path_resolution) {
        float db_value = fft_data_.at(i);

        if (std::isnan(db_value) || std::isinf(db_value)) {
            continue;
        }

        float frequency = static_cast< float >(i * bin_width);
        //        auto normalised_freq = juce::mapFromLog10(frequency, Global::MIN_HZ, Global::MAX_HZ);
        //        auto x_coord         = std::floor(normalised_freq * bounds_width);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
