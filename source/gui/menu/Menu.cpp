#include "Menu.h"

/*---------------------------------------------------------------------------
**
*/
Menu::Menu()
{
    addAndMakeVisible(theme_button_);
}

/*---------------------------------------------------------------------------
**
*/
void
Menu::resized()
{
    auto        bounds             = getLocalBounds();
    const uint8 theme_button_width = 64;

    theme_button_.setBounds(bounds.getRight() - theme_button_width, 0, theme_button_width, bounds.getHeight());
}

/*---------------------------------------------------------------------------
**
*/
ThemeButton&
Menu::getThemeButtonRef()
{
    return theme_button_;
}

/*---------------------------------------------------------------------------
** End of File
*/
