#pragma once

#include <JuceHeader.h>

class MonoWaveform : public juce::AudioVisualiserComponent
{
public:
    MonoWaveform();

    void paint(juce::Graphics& g) override;

private:
    bool theme_tracker_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoWaveform)
};
