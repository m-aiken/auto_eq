#pragma once

#include <JuceHeader.h>

class FilterFactory
{
public:
    using BandCoefficients = juce::ReferenceCountedObjectPtr< juce::dsp::IIR::Coefficients< float > >;
    using IIRFilter        = juce::dsp::IIR::Filter< float >;
    using MonoChain        = juce::dsp::ProcessorChain< IIRFilter,
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

    struct PeakBand {
        juce::AudioParameterFloat* freq_ { nullptr };
        juce::AudioParameterFloat* gain_ { nullptr };
        juce::AudioParameterFloat* q_ { nullptr };
    };

    static const uint8 NUM_BANDS;
    static const float MAX_BAND_DB_BOOST;
    static const float MAX_BAND_DB_CUT;

    enum Band {
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
    FilterFactory();

    static float getHzForBand(Band band);

    static void
    addBandToParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& parameter_layout, Band band);

    static void updatePeak(MonoChain& chain, const Band& band_id, PeakBand& params, double sample_rate);

private:
    static BandCoefficients getPeakCoefficients(double sample_rate, PeakBand& params);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterFactory)
};
