#pragma once

#include <JuceHeader.h>

class UnityGainCalculator : public juce::Thread
{
public:
    enum FIFO_ID {
        PRE_PROCESSED_FIFO,
        POST_PROCESSED_FIFO,
    };

    static constexpr uint16 CALCULATION_FREQUENCY_MS = 1000;
    static constexpr double RAMP_TIME_SECONDS        = 0.001;

public:
    explicit UnityGainCalculator(juce::RangedAudioParameter* master_gain_param);
    ~UnityGainCalculator() override;

    void run() override;

    void  prepare(const double sample_rate, const uint32 samples_per_callback);
    bool  isPrepared() const;
    void  pushForAnalysis(const juce::AudioBuffer< float >& buffer, const FIFO_ID fifo_id);
    float getGainAdjustment();

private:
    typedef juce::SmoothedValue< float, juce::ValueSmoothingTypes::Linear > SmoothedFloat;

    void calculateNextTargetValue();

    juce::RangedAudioParameter* master_gain_param_;

    SmoothedFloat unity_gain_adjustment_;

    typedef std::vector< float >   MagnitudeFifo;
    std::array< MagnitudeFifo, 2 > magnitude_fifos_;
    std::array< size_t, 2 >        write_indexes_;
    std::array< size_t, 2 >        read_indexes_;

    size_t fifo_size_;
    bool   is_prepared_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UnityGainCalculator)
};
