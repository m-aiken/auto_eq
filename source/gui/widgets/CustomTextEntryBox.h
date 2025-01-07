#pragma once

#include <JuceHeader.h>

class CustomTextEntryBox : public juce::TextEditor
{
public:
    explicit CustomTextEntryBox(const juce::String& placeholder_text = juce::String());

    void paint(juce::Graphics& g) override;
    void mouseEnter(const juce::MouseEvent& e) override;

    void resetTextColour();

private:
    static constexpr uint8_t MAX_CHARS = 32;

    const juce::String placeholder_text_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomTextEntryBox)
};
