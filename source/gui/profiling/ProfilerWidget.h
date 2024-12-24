#pragma once

#include <JuceHeader.h>

#include "MonoWaveform.h"

class ProfilerWidget : public juce::Component
{
public:
    explicit ProfilerWidget(MonoWaveform& mono_waveform_ref);

    void resized() override;

private:
    MonoWaveform& mono_waveform_ref_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProfilerWidget)
};
