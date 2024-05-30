#pragma once

#include <JuceHeader.h>

class Theme
{
public:
    typedef std::pair< juce::Colour, juce::Colour > DarkLightPair;

    static const juce::Colour WHITE;
    static const juce::Colour DARK_GREY;
    static const juce::Colour RED_ORANGE;
    static const juce::Colour SOFT_PINK;
    static const juce::Colour EGGSHELL;
    static const juce::Colour TEAL;

    static const DarkLightPair MAIN_BG;
    static const DarkLightPair TEXT;
    static const DarkLightPair FFT_PRIMARY;
    static const DarkLightPair FFT_SIDECHAIN;

    static bool dark_mode;

public:
    Theme();

    static void         toggleTheme();
    static juce::Colour getColour(DarkLightPair c);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Theme)
};
