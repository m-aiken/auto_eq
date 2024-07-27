#pragma once

#include <JuceHeader.h>

class SpinBoxButton : public juce::TextButton
{
public:
    SpinBoxButton(bool is_increment);

    void paint(juce::Graphics& g) override;
    void mouseEnter(const juce::MouseEvent& e) override;

private:
    bool is_increment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpinBoxButton)
};
