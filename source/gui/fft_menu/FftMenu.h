#pragma once

#include <JuceHeader.h>

#include "../widgets/MenuButton.h"

class FftMenu : public juce::Component
{
public:
    FftMenu(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    MenuButton primary_pre_button_;
    MenuButton primary_post_button_;
    MenuButton sidechain_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FftMenu)
};
