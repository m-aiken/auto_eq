#pragma once

#include <JuceHeader.h>

#include "AnalyserCanvas.h"
#include "DecibelMarkers.h"
#include "FrequencyMarkers.h"
#include "MonoFftPath.h"
#include "../../PluginProcessor.h"
#include "../../utility/GlobalConstants.h"

class Analyser : public juce::Component
{
public:
    Analyser(PluginProcessor& p);

    void resized() override;

private:
    DecibelMarkers   db_markers_;
    FrequencyMarkers hz_markers_;
    AnalyserCanvas   backdrop_;

    std::array< std::unique_ptr< MonoFftPath >, Global::Channels::NUM_INPUTS > fft_paths_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Analyser)
};
