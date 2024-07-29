#include "Theme.h"

const juce::Colour Theme::WHITE      = juce::Colour(255, 255, 255);
const juce::Colour Theme::DARK_GREY  = juce::Colour(32, 30, 31);
const juce::Colour Theme::RED_ORANGE = juce::Colour(255, 64, 0);
const juce::Colour Theme::SOFT_PINK  = juce::Colour(250, 170, 141);
const juce::Colour Theme::EGGSHELL   = juce::Colour(254, 239, 221);
const juce::Colour Theme::TEAL       = juce::Colour(80, 178, 192);

const Theme::DarkLightPair Theme::MAIN_BG         = DarkLightPair(DARK_GREY, WHITE);
const Theme::DarkLightPair Theme::TEXT            = DarkLightPair(EGGSHELL, DARK_GREY);
const Theme::DarkLightPair Theme::SECTION_BORDER  = DarkLightPair(WHITE.withAlpha(0.02f), DARK_GREY.withAlpha(0.1f));
const Theme::DarkLightPair Theme::DISABLED_WIDGET = DarkLightPair(WHITE.withAlpha(0.2f), DARK_GREY.withAlpha(0.4f));

const Theme::DarkLightPair Theme::ANALYSER_GRID    = DarkLightPair(EGGSHELL, DARK_GREY);
const Theme::DarkLightPair Theme::GRAPH_0DB_MARKER = DarkLightPair(RED_ORANGE, RED_ORANGE);

const Theme::DarkLightPair Theme::FFT = DarkLightPair(TEAL.withAlpha(0.2f), TEAL.withAlpha(0.2f));

const Theme::DarkLightPair Theme::BAND_BACKGROUND = DarkLightPair(WHITE.withAlpha(0.02f), DARK_GREY.withAlpha(0.1f));
const Theme::DarkLightPair Theme::BAND_VALUE = DarkLightPair(RED_ORANGE.withAlpha(0.4f), RED_ORANGE.withAlpha(0.4f));

const Theme::DarkLightPair Theme::UNITY_GAIN_VALUE_BUTTON = DarkLightPair(RED_ORANGE.withAlpha(0.4f),
                                                                          RED_ORANGE.withAlpha(0.4f));
const Theme::DarkLightPair Theme::UNITY_GAIN_VALUE_BOX    = DarkLightPair(TEAL.withAlpha(0.2f), TEAL.withAlpha(0.2f));

const Theme::DarkLightPair Theme::METER_BACKGROUND = DarkLightPair(WHITE.withAlpha(0.02f), DARK_GREY.withAlpha(0.1f));
const Theme::DarkLightPair Theme::METER_VALUE      = DarkLightPair(TEAL, TEAL);

const Theme::DarkLightPair Theme::ROTARY_FILL = DarkLightPair(TEAL.withAlpha(0.1f), RED_ORANGE.withAlpha(0.1f));
const Theme::DarkLightPair Theme::ROTARY_ARC  = DarkLightPair(TEAL, RED_ORANGE);

const Theme::DarkLightPair Theme::CHECKBOX = DarkLightPair(EGGSHELL, DARK_GREY);

const Theme::DarkLightPair Theme::RECORD_BUTTON_ON  = DarkLightPair(RED_ORANGE, RED_ORANGE);
const Theme::DarkLightPair Theme::RECORD_BUTTON_OFF = DarkLightPair(EGGSHELL, DARK_GREY);

const Theme::DarkLightPair Theme::POWER_BUTTON_ON  = DarkLightPair(TEAL, TEAL);
const Theme::DarkLightPair Theme::POWER_BUTTON_OFF = Theme::DISABLED_WIDGET;

bool Theme::dark_mode = true;

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
Theme::toggleTheme()
{
    dark_mode = !dark_mode;
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::Colour
Theme::getColour(DarkLightPair c)
{
    return dark_mode ? c.first : c.second;
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ const juce::Font
Theme::getFont()
{
    return juce::Font(juce::Font::getDefaultMonospacedFontName(), 11.f, 0);
}

/*---------------------------------------------------------------------------
** End of File
*/
