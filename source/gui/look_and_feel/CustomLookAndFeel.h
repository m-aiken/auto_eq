#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();

    void drawRotarySlider(juce::Graphics& g,
                          int             x,
                          int             y,
                          int             width,
                          int             height,
                          float           slider_pos_proportional,
                          float           rotary_start_angle,
                          float           rotary_end_angle,
                          juce::Slider&   slider) override;

    void drawLinearSlider(juce::Graphics&           g,
                          int                       x,
                          int                       y,
                          int                       width,
                          int                       height,
                          float                     slider_pos,
                          float                     min_slider_pos,
                          float                     max_slider_pos,
                          juce::Slider::SliderStyle slider_style,
                          juce::Slider&             slider) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
