#pragma once

#include "JuceHeader.h"

#include "../../PluginProcessor.h"
#include "../../dsp/Equalizer.h"

class FilterResponseCurve
    : public juce::Component
    , public juce::Timer
{
public:
    FilterResponseCurve(PluginProcessor& p);
    ~FilterResponseCurve() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

private:
    void resetMagnitudesVector();
    void calculateMagnitudes();
    int  getYCoordinateFromMagnitude(double magnitude);
    int  getBandBarHeight(double magnitude);
    void calculateXCoordinates();

private:
    PluginProcessor& processor_ref_;

    std::array< uint16, Equalizer::NUM_BANDS > x_coordinates_;
    bool                                       x_coordinates_calculated_;

    std::vector< double > magnitudes_;
    juce::Atomic< bool >  should_repaint_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseCurve)
};
