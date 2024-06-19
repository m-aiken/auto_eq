#pragma once

#include <JuceHeader.h>

#include "Equalizer.h"
#include "InputAnalysisFilter.h"

class BandUpdater : public juce::Thread
{
    typedef juce::SmoothedValue< float, juce::ValueSmoothingTypes::Linear > SmoothedFloat;
    typedef std::array< SmoothedFloat, Equalizer::NUM_BANDS >               BandDbValueArray;
    
public:
    BandUpdater(InputAnalysisFilter& analysis_filter, BandDbValueArray& band_values_array);
    ~BandUpdater() override;

    void run() override;

    void startPolling();

private:
    void updateBandValues();

    // Debug functions.
    void printBandAdjustments();

    static const uint16 UPDATE_FREQUENCY_MS;

    InputAnalysisFilter& analysis_filter_;
    BandDbValueArray&    band_values_array_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandUpdater)
};
