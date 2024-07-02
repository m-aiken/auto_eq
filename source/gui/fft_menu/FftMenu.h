#pragma once

#include <JuceHeader.h>

#include "FftMenuButton.h"

class FftMenu : public juce::Component
{
public:
    FftMenu(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    FftMenuButton primary_pre_button_;
    FftMenuButton primary_post_button_;
    FftMenuButton sidechain_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FftMenu)
};
