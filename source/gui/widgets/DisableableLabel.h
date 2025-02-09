#pragma once

#include <JuceHeader.h>

#include "Theme.h"

class DisableableLabel : public juce::Label
{
public:
    DisableableLabel(const juce::String&       component_name = juce::String(),
                     const juce::String&       label_text     = juce::String(),
                     const juce::Justification justification  = juce::Justification::centred);

    void paint(juce::Graphics& g) override;

protected:
    Theme::DarkLightPair text_colour_;
    juce::Font           font_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DisableableLabel)
};
