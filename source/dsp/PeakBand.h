#pragma once

#include <JuceHeader.h>

struct PeakBand {
    juce::AudioParameterFloat* freq_ { nullptr };
    juce::AudioParameterFloat* gain_ { nullptr };
    juce::AudioParameterFloat* q_ { nullptr };
};
