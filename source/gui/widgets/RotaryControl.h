#pragma once

#include <JuceHeader.h>

class RotaryControl
    : public juce::Slider
    , public juce::AudioProcessorParameter::Listener
{
public:
    RotaryControl(juce::AudioProcessorValueTreeState& apvts, const juce::String& parameter_id);
    ~RotaryControl();

    // Slider virtual functions.
    void paint(juce::Graphics& g) override;

    // Listener pure virtual functions.
    void parameterValueChanged(int parameter_index, float new_value) override;
    void parameterGestureChanged(int parameter_index, bool gesture_is_starting) override;

private:
    float getNormalisedValue();

    std::unique_ptr< juce::AudioProcessorValueTreeState::SliderAttachment > slider_attachment_;
    juce::RangedAudioParameter*                                             param_;

    static constexpr float START_ANGLE = juce::degreesToRadians(180.f + 45.f);
    static constexpr float END_ANGLE   = juce::degreesToRadians(180.f - 45.f) + juce::MathConstants< float >::twoPi;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryControl)
};
