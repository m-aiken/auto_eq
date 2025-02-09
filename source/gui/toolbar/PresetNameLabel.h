#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"

class PresetNameLabel : public DisableableLabel
{
public:
    PresetNameLabel(const juce::String&       component_name = juce::String(),
                    const juce::String&       label_text     = juce::String(),
                    const juce::Justification justification  = juce::Justification::centred);

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetNameLabel)
};
