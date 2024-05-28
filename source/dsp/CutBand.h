#pragma once

#include <JuceHeader.h>

struct CutBand {
    juce::AudioParameterFloat*  freq_ { nullptr };
    juce::AudioParameterChoice* slope_ { nullptr };
    juce::AudioParameterBool*   enabled_ { nullptr };
};
