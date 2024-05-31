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

    // juce::AudioProcessorParameter::Listener pure virtual functions.
    void parameterValueChanged(int parameter_index, float new_value) override;
    void parameterGestureChanged(int parameter_index, bool gesture_is_starting) override;

    // juce::Timer pure virtual function.
    void timerCallback() override;

    void addApvtsListeners();
    void removeApvtsListeners();

private:
    PluginProcessor& processor_ref_;

    juce::Atomic< bool > apvts_value_changed_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterResponseCurve)
};
