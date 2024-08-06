#pragma once

#include <JuceHeader.h>

class DisableableLabel : public juce::Label
{
public:
    DisableableLabel(const juce::String& component_name = juce::String(),
                     const juce::String& label_text     = juce::String(),
                     juce::Justification justification  = juce::Justification::centred);

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DisableableLabel)
};
