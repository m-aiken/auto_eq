#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "MonoWaveform.h"
#include "ProfilerInputWidget.h"
#include "RotaryControl.h"

class ProfilerWidget : public juce::Component
{
public:
    explicit ProfilerWidget(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DisableableLabel    label_;
    ProfilerInputWidget input_widget_;
    RotaryControl       input_trim_;
    MonoWaveform&       mono_waveform_ref_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProfilerWidget)
};
