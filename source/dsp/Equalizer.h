#pragma once

#include <JuceHeader.h>

class Equalizer
{
public:
    using IIRFilter = juce::dsp::IIR::Filter< float >;
    using MonoChain = juce::dsp::ProcessorChain< IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter,
                                                 IIRFilter >;

public:
    static constexpr uint8 NUM_BANDS = 31;

    static const float DEFAULT_BAND_DB;
    static const float DEFAULT_BAND_Q;

    enum BAND_ID {
        B1,
        B2,
        B3,
        B4,
        B5,
        B6,
        B7,
        B8,
        B9,
        B10,
        B11,
        B12,
        B13,
        B14,
        B15,
        B16,
        B17,
        B18,
        B19,
        B20,
        B21,
        B22,
        B23,
        B24,
        B25,
        B26,
        B27,
        B28,
        B29,
        B30,
        B31,
    };

public:
    Equalizer() = default;

    static float getBandHz(BAND_ID band_id);
    static float getBandTestDb(BAND_ID band_id);
    static float getBandTargetDb(BAND_ID band_id);

    static void updateBandCoefficients(MonoChain& chain, const BAND_ID& band_id, float gain, double sample_rate);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Equalizer)
};
