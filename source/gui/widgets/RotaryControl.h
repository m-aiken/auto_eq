#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class RotaryControl
    : public juce::Slider
    , public juce::AudioProcessorParameter::Listener
{
public:
    RotaryControl(juce::AudioProcessorValueTreeState& apvts,
                  const GuiParams::PARAM_ID           parameter_id,
                  const bool                          draw_text_value    = false,
                  juce::String                        suffix             = "",
                  const int                           num_decimal_places = 0);
    ~RotaryControl() override;

    // Slider virtual functions.
    void paint(juce::Graphics& g) override;
    void mouseEnter(const juce::MouseEvent& e) override;

    // Listener pure virtual functions.
    void parameterValueChanged(int parameter_index, float new_value) override;
    void parameterGestureChanged(int parameter_index, bool gesture_is_starting) override;

private:
    float getNormalisedValue();

    std::unique_ptr< juce::AudioProcessorValueTreeState::SliderAttachment > slider_attachment_;
    juce::RangedAudioParameter*                                             param_;

    bool         draw_text_value_;
    juce::String suffix_;
    int          num_decimal_places_;

    static constexpr float START_ANGLE = juce::degreesToRadians(180.f + 45.f);
    static constexpr float END_ANGLE   = juce::degreesToRadians(180.f - 45.f) + juce::MathConstants< float >::twoPi;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryControl)
};
