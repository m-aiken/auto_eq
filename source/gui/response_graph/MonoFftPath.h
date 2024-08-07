#pragma once

#include <JuceHeader.h>

#include "MonoFftBuffer.h"
#include "MonoFftPathProducer.h"
#include "Theme.h"

class MonoFftPath
    : public juce::Component
    , public juce::Timer
{
public:
    MonoFftPath(MonoFftBuffer&              fft_buffer,
                Theme::DarkLightPair        path_colour,
                juce::RangedAudioParameter* fft_enablement_param);
    ~MonoFftPath() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

private:
    MonoFftPathProducer path_producer_;

    juce::Path           path_;
    Theme::DarkLightPair path_colour_;

    juce::RangedAudioParameter* fft_enablement_param_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoFftPath)
};
