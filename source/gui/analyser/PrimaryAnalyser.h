#pragma once

#include <JuceHeader.h>

#include "AnalyserCanvas.h"
#include "DecibelMarkers.h"
#include "FrequencyMarkers.h"
#include "MonoFftPath.h"
#include "../../PluginProcessor.h"

class PrimaryAnalyser : public juce::Component
{
public:
    PrimaryAnalyser(PluginProcessor& p);

    void resized() override;

private:
    DecibelMarkers   db_markers_;
    FrequencyMarkers hz_markers_;
    AnalyserCanvas   backdrop_;

    std::unique_ptr< MonoFftPath > fft_path_primary_pre_eq_l_;
    std::unique_ptr< MonoFftPath > fft_path_primary_pre_eq_r_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PrimaryAnalyser)
};
