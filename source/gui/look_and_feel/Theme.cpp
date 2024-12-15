#include "Theme.h"

const juce::Colour Theme::DARK_GREY  = juce::Colour(37, 33, 38);
const juce::Colour Theme::PARCHMENT  = juce::Colour(250, 244, 237);
const juce::Colour Theme::RED_ORANGE = juce::Colour(214, 132, 129);
const juce::Colour Theme::TEAL       = juce::Colour(96, 153, 162);

const Theme::DLP Theme::MAIN_BG                 = DarkLightPair(DARK_GREY, PARCHMENT);
const Theme::DLP Theme::TEXT                    = DarkLightPair(PARCHMENT, DARK_GREY);
const Theme::DLP Theme::SECTION_BORDER          = DarkLightPair(PARCHMENT.withAlpha(0.02f), DARK_GREY.withAlpha(0.05f));
const Theme::DLP Theme::DISABLED_WIDGET         = DarkLightPair(PARCHMENT.withAlpha(0.2f), DARK_GREY.withAlpha(0.4f));
const Theme::DLP Theme::ANALYSER_GRID           = DarkLightPair(PARCHMENT, DARK_GREY);
const Theme::DLP Theme::GRAPH_0DB_MARKER        = DarkLightPair(RED_ORANGE, RED_ORANGE);
const Theme::DLP Theme::FFT                     = DarkLightPair(TEAL.withAlpha(0.2f), TEAL.withAlpha(0.2f));
const Theme::DLP Theme::BAND_BACKGROUND         = DarkLightPair(PARCHMENT.withAlpha(0.02f), DARK_GREY.withAlpha(0.1f));
const Theme::DLP Theme::BAND_VALUE              = DarkLightPair(RED_ORANGE, RED_ORANGE);
const Theme::DLP Theme::GHOST_NODE              = DarkLightPair(RED_ORANGE.withAlpha(0.2f), RED_ORANGE.withAlpha(0.2f));
const Theme::DLP Theme::UNITY_GAIN_VALUE_BUTTON = DarkLightPair(RED_ORANGE.withAlpha(0.4f), RED_ORANGE.withAlpha(0.4f));
const Theme::DLP Theme::UNITY_GAIN_VALUE_BOX    = DarkLightPair(TEAL.withAlpha(0.2f), TEAL.withAlpha(0.2f));
const Theme::DLP Theme::METER_BACKGROUND        = DarkLightPair(PARCHMENT.withAlpha(0.02f), DARK_GREY.withAlpha(0.1f));
const Theme::DLP Theme::METER_VALUE             = DarkLightPair(TEAL.withAlpha(0.4f), TEAL.withAlpha(0.4f));
const Theme::DLP Theme::ROTARY_FILL             = DarkLightPair(TEAL.withAlpha(0.1f), RED_ORANGE.withAlpha(0.1f));
const Theme::DLP Theme::ROTARY_ARC              = DarkLightPair(TEAL, RED_ORANGE);
const Theme::DLP Theme::CHECKBOX                = DarkLightPair(PARCHMENT, DARK_GREY);
const Theme::DLP Theme::RECORD_BUTTON           = DarkLightPair(RED_ORANGE, RED_ORANGE);
const Theme::DLP Theme::STOP_BUTTON             = DarkLightPair(RED_ORANGE, RED_ORANGE);
const Theme::DLP Theme::POWER_BUTTON_ON         = DarkLightPair(TEAL, TEAL);
const Theme::DLP Theme::POWER_BUTTON_OFF        = Theme::DISABLED_WIDGET;
const Theme::DLP Theme::TEXT_BTN_BG             = DarkLightPair(PARCHMENT.withAlpha(0.02f), DARK_GREY.withAlpha(0.05f));
const Theme::DLP Theme::TEXT_BTN_BG_FOCUS       = DarkLightPair(PARCHMENT.withAlpha(0.05f), DARK_GREY.withAlpha(0.1f));
const Theme::DLP Theme::TEXT_BTN_TOGGLE_ON_BORDER = DarkLightPair(RED_ORANGE, RED_ORANGE);

bool Theme::app_is_in_dark_mode = true;

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
Theme::toggleTheme()
{
    app_is_in_dark_mode = !app_is_in_dark_mode;
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::Colour
Theme::getColour(DarkLightPair c)
{
    return app_is_in_dark_mode ? c.first : c.second;
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
