#pragma once

#include <JuceHeader.h>

class IntensityControl : public juce::Component
{
public:
    IntensityControl(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Label  label_;
    juce::Slider slider_;

    std::unique_ptr< juce::AudioProcessorValueTreeState::SliderAttachment > slider_attachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntensityControl)
};
