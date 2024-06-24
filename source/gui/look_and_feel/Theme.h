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
    static const DarkLightPair ANALYSER_GRID;
    static const DarkLightPair GRAPH_0DB_MARKER;
    static const DarkLightPair FFT_PRIMARY_PRE_EQ;
    static const DarkLightPair FFT_PRIMARY_POST_EQ;
    static const DarkLightPair FFT_SIDECHAIN;
    static const DarkLightPair FILTER_RESPONSE_PATH;

    static const DarkLightPair METER_COLD;
    static const DarkLightPair METER_HOT;

    static const DarkLightPair ROTARY_FILL;
    static const DarkLightPair ROTARY_ARC;

    static bool dark_mode;

public:
    Theme() = default;

    static void         toggleTheme();
    static juce::Colour getColour(DarkLightPair c);

    static const juce::Font getFont();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Theme)
};
