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
    DisableableLabel    input_level_label_;
    ProfilerInputWidget input_meter_widget_;
    RotaryControl       input_trim_rotary_;
    MonoWaveform&       mono_waveform_ref_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProfilerWidget)
};
