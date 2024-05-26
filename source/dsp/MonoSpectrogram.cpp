#include "MonoSpectrogram.h"

/*---------------------------------------------------------------------------
**
*/
MonoSpectrogram::MonoSpectrogram(MonoFftBuffer& fft_buffer)
    : fft_(MonoFftBuffer::FFT_ORDER)
    , windowing_fn_(MonoFftBuffer::FFT_SIZE, juce::dsp::WindowingFunction< float >::blackmanHarris)
    , fft_buffer_(fft_buffer)
{
    std::fill(fft_data_.begin(), fft_data_.end(), 0.f);

    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
MonoSpectrogram::~MonoSpectrogram()
{
    stopTimer();
}

/*---------------------------------------------------------------------------
**
*/
void
MonoSpectrogram::paint(juce::Graphics& g)
{
}

/*---------------------------------------------------------------------------
**
*/
void
MonoSpectrogram::timerCallback()
{
    processFftData();
    generatePath();
    repaint();
}

/*---------------------------------------------------------------------------
**
*/
void
MonoSpectrogram::processFftData()
{
    fft_buffer_.getNextBlock(fft_data_);
    windowing_fn_.multiplyWithWindowingTable(fft_data_.data(), MonoFftBuffer::FFT_SIZE);
    fft_.performFrequencyOnlyForwardTransform(fft_data_.data(), true);

    int num_bins = std::floor(MonoFftBuffer::FFT_SIZE * 0.5);
    juce::FloatVectorOperations::multiply(fft_data_.data(), 1.f / static_cast< float >(num_bins), num_bins + 1);

    for (size_t i = 0; i < fft_data_.size(); ++i) {
        fft_data_.at(i) = juce::Decibels::gainToDecibels(fft_data_.at(i), -48.f);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
MonoSpectrogram::generatePath()
{
}

/*---------------------------------------------------------------------------
** End of File
*/
