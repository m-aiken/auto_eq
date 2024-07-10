#pragma once

#include <JuceHeader.h>

#include "../../dsp/MonoFftBuffer.h"

class MonoFftPathProducer : juce::Thread
{
public:
    MonoFftPathProducer(MonoFftBuffer& fft_buffer);
    ~MonoFftPathProducer();

    void prepare(const juce::Rectangle< int >& bounds);

    void run() override;

    juce::Path& getPath();

    void updateDrawableBounds(const juce::Rectangle< int >& bounds);

private:
    void  processFftData();
    void  generatePath();
    float getYCoordinate(const float& sample);

    static constexpr size_t             FIFO_SIZE = 8;
    std::array< juce::Path, FIFO_SIZE > fifo_;
    size_t                              fifo_write_idx_;
    size_t                              fifo_read_idx_;

    juce::dsp::FFT                        fft_;
    MonoFftBuffer::FftDataBlock           fft_data_;
    juce::dsp::WindowingFunction< float > windowing_fn_;
    MonoFftBuffer&                        fft_buffer_;

    juce::Rectangle< int > drawable_bounds_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoFftPathProducer)
};
