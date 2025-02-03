#include "Theme.h"
#include "ThemeButton.h"

/*---------------------------------------------------------------------------
**
*/
ThemeButton::ThemeButton()
    : CustomTextButton("Theme")
{
    setButtonText(Theme::app_is_in_dark_mode ? "Light" : "Dark");

    onClick = [this]() {
        Theme::toggleTheme();
        setButtonText(Theme::app_is_in_dark_mode ? "Light" : "Dark");
        repaint();
    };
}

/*---------------------------------------------------------------------------
** End of File
*/
