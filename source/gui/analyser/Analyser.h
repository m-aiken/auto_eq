#pragma once

#include <JuceHeader.h>

#include "AnalyserCanvas.h"
#include "MonoSpectrogramPath.h"
#include "../../PluginProcessor.h"

class Analyser : public juce::Component
{
public:
    Analyser(PluginProcessor& p);

    void resized() override;

private:
    AnalyserCanvas      backdrop_;
    MonoSpectrogramPath spectrogram_path_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Analyser)
};
