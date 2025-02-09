#pragma once

#include <JuceHeader.h>

class Theme
{
public:
    typedef std::pair< juce::Colour, juce::Colour > DarkLightPair;

    static const juce::Colour DARK_GREY;
    static const juce::Colour PARCHMENT;
    static const juce::Colour RED_ORANGE;
    static const juce::Colour TEAL;

    static const DarkLightPair MAIN_BG;
    static const DarkLightPair TEXT;
    static const DarkLightPair SECTION_BORDER;
    static const DarkLightPair DISABLED_WIDGET;
    static const DarkLightPair ANALYSER_GRID;
    static const DarkLightPair GRAPH_0DB_MARKER;
    static const DarkLightPair FFT;
    static const DarkLightPair BAND_BACKGROUND;
    static const DarkLightPair BAND_VALUE;
    static const DarkLightPair GHOST_NODE;
    static const DarkLightPair UNITY_GAIN_VALUE_BUTTON;
    static const DarkLightPair UNITY_GAIN_VALUE_BOX;
    static const DarkLightPair METER_BACKGROUND;
    static const DarkLightPair METER_VALUE;
    static const DarkLightPair ROTARY_FILL;
    static const DarkLightPair ROTARY_ARC;
    static const DarkLightPair CHECKBOX;
    static const DarkLightPair RECORD_BUTTON;
    static const DarkLightPair STOP_BUTTON;
    static const DarkLightPair POWER_BUTTON_ON;
    static const DarkLightPair POWER_BUTTON_OFF;
    static const DarkLightPair TOOLBAR_SEPARATOR;
    static const DarkLightPair TEXT_BTN_BG;
    static const DarkLightPair TEXT_BTN_BG_FOCUS;
    static const DarkLightPair TEXT_BTN_TOGGLE_ON_BORDER;
    static const DarkLightPair TEXTBOX_BG;
    static const DarkLightPair READONLY_TEXTBOX_BG;
    static const DarkLightPair MENU_ITEM_BG;
    static const DarkLightPair MENU_ITEM_BG_FOCUS;
    static const DarkLightPair WARNING_TEXT;
    static const DarkLightPair DEFAULT_PRESET_NAME_TEXT;

    static bool app_is_in_dark_mode;

public:
    Theme() = default;

    static void         toggleTheme();
    static juce::Colour getColour(DarkLightPair c);

    static const juce::Font getFont();

private:
    // This second typedef is purely so that the definitions in the cpp file are tidyer.
    // Other classes referencing the type use DarkLightPair.
    typedef DarkLightPair DLP;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Theme)
};
