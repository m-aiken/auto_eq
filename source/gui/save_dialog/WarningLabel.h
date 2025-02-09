#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"

class WarningLabel : public DisableableLabel
{
public:
    WarningLabel(const juce::String&       component_name = juce::String(),
                 const juce::String&       label_text     = juce::String(),
                 const juce::Justification justification  = juce::Justification::centred);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WarningLabel)
};
