#pragma once

#include <JuceHeader.h>

#include "Equalizer.h"
#include "InputAnalysisFilter.h"

class BandUpdater : public juce::Thread
{
public:
    typedef juce::SmoothedValue< float, juce::ValueSmoothingTypes::Linear > SmoothedFloat;
    typedef std::array< SmoothedFloat, Equalizer::NUM_BANDS >               BandDbValueArray;

    static constexpr uint16 UPDATE_FREQUENCY_MS = 1000;

public:
    explicit BandUpdater(InputAnalysisFilter& analysis_filter);
    ~BandUpdater() override;

    void prepare(const double sample_rate);
    bool isPrepared() const;

    void run() override;

    float getBandDb(const Equalizer::BAND_ID band_id);
    void  syncroniseWithTreeState(const juce::AudioProcessorValueTreeState& apvts);

private:
    static constexpr double BAND_DB_RAMP_TIME_SECONDS = 0.02;

    void updateBandValues();
    void printBandAdjustments();

    InputAnalysisFilter& analysis_filter_;
    BandDbValueArray     band_values_array_;
    bool                 is_prepared_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandUpdater)
};
