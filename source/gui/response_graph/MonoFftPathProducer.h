#pragma once

#include <JuceHeader.h>

#include "MonoFftBuffer.h"

class MonoFftPathProducer : juce::Thread
{
public:
    explicit MonoFftPathProducer(MonoFftBuffer& fft_buffer);
    ~MonoFftPathProducer() override;

    void prepare(const juce::Rectangle< int >& bounds);

    void run() override;

    juce::Path& getPath();

private:
    void  processFftData();
    void  generatePath();
    float getYCoordinate(const float& sample) const;

    static constexpr size_t             FIFO_SIZE = 8;
    std::array< juce::Path, FIFO_SIZE > fifo_;
    size_t                              fifo_write_idx_;
    size_t                              fifo_read_idx_;

    juce::dsp::FFT                        fft_;
    MonoFftBuffer::FftDataBlock           fft_data_;
    juce::dsp::WindowingFunction< float > windowing_fn_;
    MonoFftBuffer&                        fft_buffer_;

    juce::Rectangle< int > drawable_bounds_;

    static constexpr uint8 PATH_RESOLUTION = 2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoFftPathProducer)
};
