#pragma once

#include "JuceHeader.h"

#include "../../PluginProcessor.h"
#include "../../dsp/Equalizer.h"

class FilterResponseBands
    : public juce::Component
    , public juce::Timer
{
public:
    FilterResponseBands(PluginProcessor& p);
    ~FilterResponseBands() override;

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
    static const uint8 BAR_WIDTH;
    static const uint8 HALF_BAR_WIDTH;

    PluginProcessor& processor_ref_;

    std::array< uint16, Equalizer::NUM_BANDS > x_coordinates_;
    bool                                       x_coordinates_calculated_;

    std::vector< double > magnitudes_;
    juce::Atomic< bool >  should_repaint_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseBands)
};
