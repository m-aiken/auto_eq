#pragma once

#include <JuceHeader.h>

#include "Equalizer.h"
#include "InputAnalysisFilter.h"

class BandUpdater : public juce::Thread
{
public:
    BandUpdater(InputAnalysisFilter& analysis_filter, juce::AudioProcessorValueTreeState& apvts);
    ~BandUpdater() override;

    void run() override;

private:
    void                       updateBandValues();
    juce::AudioParameterFloat* getBandParameter(Equalizer::BAND_ID band_id);

    // Debug functions.
    void printBandAdjustments();

    static const uint16 UPDATE_FREQUENCY_MS;

    InputAnalysisFilter&                analysis_filter_;
    juce::AudioProcessorValueTreeState& apvts_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandUpdater)
};
