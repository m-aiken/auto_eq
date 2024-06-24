#pragma once

#include <JuceHeader.h>

#include "../look_and_feel/Theme.h"
#include "../../dsp/MonoFftBuffer.h"
#include "../../utility/GlobalConstants.h"

class MonoFftPath
    : public juce::Component
    , public juce::Timer
{
public:
    MonoFftPath(MonoFftBuffer& fft_buffer, Theme::DarkLightPair path_colour, Global::PATH_DISPLAY_MODE display_mode);
    ~MonoFftPath() override;

    void paint(juce::Graphics& g) override;

    void timerCallback() override;

private:
    void processFftData();
    void generatePath();

    juce::dsp::FFT                        fft_;
    MonoFftBuffer::FftDataBlock           fft_data_;
    juce::dsp::WindowingFunction< float > windowing_fn_;
    MonoFftBuffer&                        fft_buffer_;
    juce::Path                            path_;
    Theme::DarkLightPair                  path_colour_;
    Global::PATH_DISPLAY_MODE             display_mode_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoFftPath)
};
