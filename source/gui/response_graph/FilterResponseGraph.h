#pragma once

#include "JuceHeader.h"

#include "DecibelMarkers.h"
#include "FilterResponseCanvas.h"
#include "FilterResponseBands.h"
#include "FrequencyMarkers.h"
#include "MonoFftPath.h"
#include "../../PluginProcessor.h"

class FilterResponseGraph : public juce::Component
{
public:
    FilterResponseGraph(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    FilterResponseCanvas backdrop_;
    DecibelMarkers       db_scale_;
    FrequencyMarkers     hz_scale_;
    FilterResponseBands  eq_bands_;

    std::unique_ptr< MonoFftPath > fft_path_primary_post_eq_l_;
    std::unique_ptr< MonoFftPath > fft_path_primary_post_eq_r_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseGraph)
};
