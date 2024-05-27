#pragma once

#include <JuceHeader.h>

#include "AnalyserCanvas.h"
#include "MonoSpectrogramPath.h"
#include "../../PluginProcessor.h"
#include "../../utility/GlobalConstants.h"

class Analyser : public juce::Component
{
public:
    Analyser(PluginProcessor& p);

    void resized() override;

private:
    AnalyserCanvas                                                                     backdrop_;
    std::array< std::unique_ptr< MonoSpectrogramPath >, Global::Channels::NUM_INPUTS > spectrogram_paths_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Analyser)
};
