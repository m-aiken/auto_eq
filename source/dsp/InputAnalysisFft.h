#pragma once

#include <JuceHeader.h>

#include "MonoFftBuffer.h"

class InputAnalysisFft : public juce::Timer
{
public:
    InputAnalysisFft(MonoFftBuffer& fft_buffer, juce::AudioProcessorValueTreeState& apvts);
    ~InputAnalysisFft();

    void timerCallback() override;

private:
    void processFftData();
    void updateFilterBands();

    juce::dsp::FFT                        fft_;
    MonoFftBuffer::FftDataBlock           fft_data_;
    juce::dsp::WindowingFunction< float > windowing_fn_;
    MonoFftBuffer&                        fft_buffer_;

    juce::AudioProcessorValueTreeState& apvts_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputAnalysisFft)
};
