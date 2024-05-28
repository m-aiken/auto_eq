#pragma once

#include <JuceHeader.h>

class FilterFactory
{
public:
    using Filter    = juce::dsp::IIR::Filter< float >;
    using CutFilter = juce::dsp::ProcessorChain< Filter, Filter, Filter, Filter >;
    using MonoChain = juce::dsp::ProcessorChain< CutFilter, Filter, Filter, Filter, Filter, Filter, Filter, CutFilter >;
    using Coefficients = juce::ReferenceCountedArray< juce::dsp::FilterDesign< float >::IIRCoefficients >;

    enum ChainPosition {
        LOW_CUT,
        PEAK_1,
        PEAK_2,
        PEAK_3,
        PEAK_4,
        PEAK_5,
        PEAK_6,
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
