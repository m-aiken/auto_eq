#pragma once

#include <JuceHeader.h>

#include "../../dsp/MonoFftBuffer.h"

class MonoSpectrogramPath
    : public juce::Component
    , public juce::Timer
{
public:
    MonoSpectrogramPath(MonoFftBuffer& fft_buffer, const juce::Colour& path_colour);
    ~MonoSpectrogramPath();

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
    juce::Colour                          path_colour_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoSpectrogramPath)
};
