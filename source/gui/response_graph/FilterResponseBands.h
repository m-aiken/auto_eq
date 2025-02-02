#pragma once

#include <JuceHeader.h>

#include "EqBandSlider.h"
#include "Equalizer.h"
#include "FilterMagnitudesCalculator.h"
#include "PluginProcessor.h"

class FilterResponseBands : public juce::Component
{
public:
    explicit FilterResponseBands(PluginProcessor& p);

    void resized() override;

private:
    int  getYCoordinateFromMagnitude(const double magnitude) const;
    void updateSliderValues();
    int  getBandBarHeight(const double magnitude) const;
    void calculateXCoordinates();

private:
    static const uint8 BAR_WIDTH;
    static const uint8 HALF_BAR_WIDTH;

    std::array< int, Equalizer::NUM_BANDS > x_coordinates_;
    bool                                    x_coordinates_calculated_;

    std::array< std::unique_ptr< EqBandSlider >, Equalizer::NUM_BANDS > sliders_;

    FilterMagnitudesCalculator magnitudes_calculator_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseBands)
};
