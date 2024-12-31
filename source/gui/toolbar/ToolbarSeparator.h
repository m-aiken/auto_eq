#pragma once

#include <JuceHeader.h>

class ToolbarSeparator : public juce::Component
{
public:
    ToolbarSeparator() = default;

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToolbarSeparator)
};
