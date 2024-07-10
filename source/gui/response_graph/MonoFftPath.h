#pragma once

#include <JuceHeader.h>

#include "MonoFftPathProducer.h"
#include "../look_and_feel/Theme.h"
#include "../../dsp/MonoFftBuffer.h"
#include "../../utility/GlobalConstants.h"

class MonoFftPath
    : public juce::Component
    , public juce::Timer
{
public:
    MonoFftPath(MonoFftBuffer&              fft_buffer,
                Theme::DarkLightPair        path_colour,
                Global::PATH_DISPLAY_MODE   display_mode,
                juce::RangedAudioParameter* fft_enablement_param);
    ~MonoFftPath() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

private:
    MonoFftPathProducer path_producer_;

    juce::Path                path_;
    Theme::DarkLightPair      path_colour_;
    Global::PATH_DISPLAY_MODE display_mode_;

    juce::RangedAudioParameter* fft_enablement_param_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoFftPath)
};
