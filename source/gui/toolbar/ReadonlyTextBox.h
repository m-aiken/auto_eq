#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"

class ReadonlyTextBox : public juce::Component
{
public:
    explicit ReadonlyTextBox(const juce::String& initial_text);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setText(const juce::String& text);

private:
    DisableableLabel label_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReadonlyTextBox)
};
