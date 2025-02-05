#pragma once

#include <JuceHeader.h>

class MonoFftBuffer
{
public:
    // This enum represents how much we need to shift by to get various FFT sizes.
    enum {
        SIZE_1024  = 10,
        SIZE_2048  = 11,
        SIZE_4096  = 12,
        SIZE_8192  = 13,
        SIZE_16348 = 14,
        SIZE_32768 = 15,
    };

    // FFT constants.
    static constexpr uint8  FFT_ORDER = SIZE_16348;
    static constexpr size_t FFT_SIZE  = 1 << FFT_ORDER;
    static constexpr size_t NUM_BINS  = FFT_SIZE * 0.5;

    typedef std::array< float, FFT_SIZE * 2 > FftDataBlock;

public:
    MonoFftBuffer();

    void   prepare(const double sample_rate);
    void   pushNextSample(const float sample);
    void   getNextBlock(FftDataBlock& block) const;
    double getBinWidth() const;
    bool   isPrepared() const;

private:
    double                        sample_rate_;
    std::array< float, FFT_SIZE > ring_buffer_;
    size_t                        buffer_index_;
    bool                          is_prepared_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoFftBuffer)
};
