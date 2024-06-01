#pragma once

#include <JuceHeader.h>

#include "../../PluginProcessor.h"

class FilterResponseCurve
    : public juce::Component
    , public juce::AudioProcessorParameter::Listener
    , public juce::Timer
{
public:
    FilterResponseCurve(PluginProcessor& p);
    ~FilterResponseCurve();

    void paint(juce::Graphics& g) override;
    void resized() override;

    // juce::AudioProcessorParameter::Listener pure virtual functions.
    void parameterValueChanged(int parameter_index, float new_value) override;
    void parameterGestureChanged(int parameter_index, bool gesture_is_starting) override;

    // juce::Timer pure virtual function.
    void timerCallback() override;

private:
    void addApvtsListeners();
    void removeApvtsListeners();

    void resetMagnitudesVector();
    void calculateMagnitudes();
    int  getYCoordinateFromMagnitude(double magnitude);
    void plotPath();

private:
    PluginProcessor& processor_ref_;

    std::vector< double > magnitudes_;
    juce::Path            path_;
    juce::Atomic< bool >  should_repaint_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseCurve)
};
