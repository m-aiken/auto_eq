#pragma once

#include <JuceHeader.h>

#include "Equalizer.h"
#include "InputAnalysisFilter.h"

class BandUpdater : public juce::Thread
{
public:
    typedef juce::SmoothedValue< float, juce::ValueSmoothingTypes::Linear > SmoothedFloat;
    typedef std::array< SmoothedFloat, Equalizer::NUM_BANDS >               BandDbValueArray;

    static const uint16 UPDATE_FREQUENCY_MS;

public:
    BandUpdater(InputAnalysisFilter& analysis_filter);
    ~BandUpdater() override;

    void prepare(double sample_rate);
    bool isPrepared() const;

    void run() override;

    float getBandDb(Equalizer::BAND_ID band_id);

    void syncroniseWithTreeState(juce::AudioProcessorValueTreeState& apvts);

private:
    void updateBandValues();

    // Debug functions.
    void printBandAdjustments();

    static const double BAND_DB_RAMP_TIME_SECONDS;

    InputAnalysisFilter& analysis_filter_;
    BandDbValueArray     band_values_array_;

    bool is_prepared_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandUpdater)
};
