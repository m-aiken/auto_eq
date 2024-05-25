#pragma once

#include <JuceHeader.h>

#include "MonoFftBuffer.h"

class Spectrogram
    : public juce::Component
    , public juce::Timer
{
public:
    Spectrogram(MonoFftBuffer& fft_buffer);
    ~Spectrogram();

    void paint(juce::Graphics& g) override;

    void timerCallback() override;

    void processFftData();
    void generatePath();

private:
    juce::dsp::FFT                        fft_;
    MonoFftBuffer::FftDataBlock           fft_data_;
    juce::dsp::WindowingFunction< float > windowing_fn_;
    MonoFftBuffer&                        fft_buffer_;
    juce::Path                            path_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Spectrogram)
};
