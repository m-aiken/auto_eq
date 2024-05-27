#pragma once

#include <JuceHeader.h>

#include "AnalyserCanvas.h"
#include "MonoFftPath.h"
#include "../../PluginProcessor.h"
#include "../../utility/GlobalConstants.h"

class Analyser : public juce::Component
{
public:
    Analyser(PluginProcessor& p);

    void resized() override;

private:
    AnalyserCanvas                                                             backdrop_;
    std::array< std::unique_ptr< MonoFftPath >, Global::Channels::NUM_INPUTS > fft_paths_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Analyser)
};
