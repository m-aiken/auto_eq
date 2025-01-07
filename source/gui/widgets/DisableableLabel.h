#pragma once

#include <JuceHeader.h>

class DisableableLabel : public juce::Label
{
public:
    DisableableLabel(const juce::String&       component_name = juce::String(),
                     const juce::String&       label_text     = juce::String(),
                     const juce::Justification justification  = juce::Justification::centred,
                     const bool                is_warning     = false);

    void paint(juce::Graphics& g) override;

private:
    bool       is_warning_label_;
    juce::Font font_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DisableableLabel)
};
