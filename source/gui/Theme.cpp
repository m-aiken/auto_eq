#include "Theme.h"

/*static*/ const juce::Colour Theme::WHITE      = juce::Colour(255, 255, 255);
/*static*/ const juce::Colour Theme::DARK_GREY  = juce::Colour(32, 30, 31);
/*static*/ const juce::Colour Theme::RED_ORANGE = juce::Colour(255, 64, 0);
/*static*/ const juce::Colour Theme::SOFT_PINK  = juce::Colour(250, 170, 141);
/*static*/ const juce::Colour Theme::EGGSHELL   = juce::Colour(254, 239, 221);
/*static*/ const juce::Colour Theme::TEAL       = juce::Colour(80, 178, 192);

/*static*/ const Theme::DarkLightPair Theme::MAIN_BG       = DarkLightPair(DARK_GREY, WHITE);
/*static*/ const Theme::DarkLightPair Theme::TEXT          = DarkLightPair(EGGSHELL, DARK_GREY);
/*static*/ const Theme::DarkLightPair Theme::FFT_PRIMARY   = DarkLightPair(TEAL, TEAL);
/*static*/ const Theme::DarkLightPair Theme::FFT_SIDECHAIN = DarkLightPair(SOFT_PINK, SOFT_PINK);

/*static*/ bool Theme::dark_mode = false;

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
** End of File
*/
