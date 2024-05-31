#pragma once

#include <JuceHeader.h>

#include "AnalyserCanvas.h"
#include "DecibelMarkers.h"
#include "FrequencyMarkers.h"
#include "MonoFftPath.h"
#include "../../PluginProcessor.h"

class SidechainAnalyser : public juce::Component
{
public:
    SidechainAnalyser(PluginProcessor& p);

    void resized() override;

private:
    DecibelMarkers   db_markers_;
    FrequencyMarkers hz_markers_;
    AnalyserCanvas   backdrop_;

    std::unique_ptr< MonoFftPath > fft_path_sidechain_l_;
    std::unique_ptr< MonoFftPath > fft_path_sidechain_r_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SidechainAnalyser)
};
