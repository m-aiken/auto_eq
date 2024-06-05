#pragma once

#include <JuceHeader.h>

class FilterFactory
{
public:
    using IIRFilter            = juce::dsp::IIR::Filter< float >;
    using Peak                 = IIRFilter;
    using Shelf                = IIRFilter;
    using Cut                  = juce::dsp::ProcessorChain< IIRFilter, IIRFilter, IIRFilter, IIRFilter >;
    using MonoChain            = juce::dsp::ProcessorChain< Cut, Shelf, Peak, Peak, Peak, Peak, Peak, Shelf, Cut >;
    using RefCtObjCoefficients = juce::ReferenceCountedObjectPtr< juce::dsp::IIR::Coefficients< float > >;
    using RefCtArrCoefficients = juce::ReferenceCountedArray< juce::dsp::FilterDesign< float >::IIRCoefficients >;

    enum ChainPosition {
        LOW_CUT,
        LOW_SHELF,
        PEAK_1,
        PEAK_2,
        PEAK_3,
        PEAK_4,
        PEAK_5,
        HIGH_SHELF,
        HIGH_CUT,
    };

    enum Slope {
        SLOPE_12,
        SLOPE_24,
        SLOPE_36,
        SLOPE_48,
    };

    struct CutBand {
        juce::AudioParameterFloat*  freq_ { nullptr };
        juce::AudioParameterChoice* slope_ { nullptr };
        juce::AudioParameterBool*   enabled_ { nullptr };
    };

    struct ShelfBand {
        juce::AudioParameterFloat* freq_ { nullptr };
        juce::AudioParameterFloat* gain_ { nullptr };
        juce::AudioParameterFloat* q_ { nullptr };
    };

    struct PeakBand {
        juce::AudioParameterFloat* freq_ { nullptr };
        juce::AudioParameterFloat* gain_ { nullptr };
        juce::AudioParameterFloat* q_ { nullptr };
    };

    struct BandSet {
        CutBand   low_cut_;
        ShelfBand low_shelf_;
        PeakBand  peak_1_;
        PeakBand  peak_2_;
        PeakBand  peak_3_;
        PeakBand  peak_4_;
        PeakBand  peak_5_;
        ShelfBand high_shelf_;
        CutBand   high_cut_;
    };

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

    static void updateLowCut(MonoChain& chain, CutBand& params, double sample_rate);
    static void updateHighCut(MonoChain& chain, CutBand& params, double sample_rate);
    static void updateLowShelf(MonoChain& chain, ShelfBand& params, double sample_rate);
    static void updateHighShelf(MonoChain& chain, ShelfBand& params, double sample_rate);
    static void updatePeak(MonoChain& chain, const ChainPosition& position, PeakBand& params, double sample_rate);

private:
    static RefCtArrCoefficients getLowCutCoefficients(double sample_rate, CutBand& params);
    static RefCtArrCoefficients getHighCutCoefficients(double sample_rate, CutBand& params);
    static RefCtObjCoefficients getLowShelfCoefficients(double sample_rate, ShelfBand& params);
    static RefCtObjCoefficients getHighShelfCoefficients(double sample_rate, ShelfBand& params);
    static RefCtObjCoefficients getPeakCoefficients(double sample_rate, PeakBand& params);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterFactory)
};
