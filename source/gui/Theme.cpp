#include "Theme.h"

/*static*/ const juce::Colour Theme::WHITE      = juce::Colour(255, 255, 255);
/*static*/ const juce::Colour Theme::DARK_GREY  = juce::Colour(32, 30, 31);
/*static*/ const juce::Colour Theme::RED_ORANGE = juce::Colour(255, 64, 0);
/*static*/ const juce::Colour Theme::SOFT_PINK  = juce::Colour(250, 170, 141);
/*static*/ const juce::Colour Theme::EGGSHELL   = juce::Colour(254, 239, 221);
/*static*/ const juce::Colour Theme::TEAL       = juce::Colour(80, 178, 192);

/*static*/ const Theme::DarkLightPair Theme::MAIN_BG              = DarkLightPair(DARK_GREY, WHITE);
/*static*/ const Theme::DarkLightPair Theme::TEXT                 = DarkLightPair(EGGSHELL, DARK_GREY);
/*static*/ const Theme::DarkLightPair Theme::ANALYSER_GRID        = DarkLightPair(EGGSHELL, DARK_GREY);
/*static*/ const Theme::DarkLightPair Theme::GRAPH_0DB_MARKER     = DarkLightPair(RED_ORANGE, RED_ORANGE);
/*static*/ const Theme::DarkLightPair Theme::FFT_PRIMARY_PRE_EQ   = DarkLightPair(TEAL.withAlpha(0.2f),
                                                                                TEAL.withAlpha(0.2f));
/*static*/ const Theme::DarkLightPair Theme::FFT_PRIMARY_POST_EQ  = DarkLightPair(TEAL, TEAL);
/*static*/ const Theme::DarkLightPair Theme::FFT_SIDECHAIN        = DarkLightPair(EGGSHELL.withAlpha(0.2f),
                                                                           DARK_GREY.withAlpha(0.1f));
/*static*/ const Theme::DarkLightPair Theme::FILTER_RESPONSE_PATH = DarkLightPair(RED_ORANGE.withAlpha(0.4f),
                                                                                  RED_ORANGE.withAlpha(0.4f));

/*static*/ const Theme::DarkLightPair Theme::METER_COLD = DarkLightPair(TEAL.withAlpha(0.5f), TEAL.withAlpha(0.5f));
/*static*/ const Theme::DarkLightPair Theme::METER_HOT  = DarkLightPair(RED_ORANGE.withAlpha(0.5f),
                                                                       RED_ORANGE.withAlpha(0.5f));

/*static*/ bool Theme::dark_mode = true;

/*---------------------------------------------------------------------------
**
*/
Theme::Theme()
{
}

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
