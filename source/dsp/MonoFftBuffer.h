#pragma once

#include <JuceHeader.h>

class MonoFftBuffer
{
public:
    // This enum represents how much we need to shift by to get various FFT sizes.
    enum {
        SIZE_1024 = 10,
        SIZE_2048 = 11,
        SIZE_4096 = 12,
    };

    // FFT constants.
    enum {
        FFT_ORDER     = SIZE_2048,
        FFT_SIZE      = 1 << FFT_ORDER,
        FFT_DATA_SIZE = FFT_SIZE * 2,
    };

    typedef std::array< float, FFT_DATA_SIZE > FftDataBlock;

public:
    MonoFftBuffer();

    void prepare(double sample_rate);

    void pushNextSample(float sample);
    void getNextBlock(FftDataBlock& block);

    double getBinWidth();

    bool isPrepared() const;

private:
    double                        sample_rate_;
    std::array< float, FFT_SIZE > ring_buffer_;
    size_t                        buffer_index_;

    bool is_prepared_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoFftBuffer)
};
