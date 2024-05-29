#pragma once

#include <JuceHeader.h>

class FilterFactory
{
public:
    using IIRFilter    = juce::dsp::IIR::Filter< float >;
    using Peak         = IIRFilter;
    using Shelf        = IIRFilter;
    using Cut          = juce::dsp::ProcessorChain< IIRFilter, IIRFilter, IIRFilter, IIRFilter >;
    using MonoChain    = juce::dsp::ProcessorChain< Cut, Shelf, Peak, Peak, Peak, Peak, Peak, Shelf, Cut >;
    using Coefficients = juce::ReferenceCountedArray< juce::dsp::FilterDesign< float >::IIRCoefficients >;

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

public:
    FilterFactory();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterFactory)
};
