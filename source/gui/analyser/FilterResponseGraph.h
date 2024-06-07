#pragma once

#include <JuceHeader.h>

#include "AnalyserCanvas.h"
#include "FilterResponseCurve.h"
#include "FrequencyMarkers.h"
#include "../DecibelMarkers.h"
#include "../../PluginProcessor.h"

class FilterResponseGraph : public juce::Component
{
public:
    FilterResponseGraph(PluginProcessor& p);

    void resized() override;

private:
    AnalyserCanvas      backdrop_;
    DecibelMarkers      db_scale_;
    FrequencyMarkers    hz_scale_;
    FilterResponseCurve response_curve_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseGraph)
};
