#pragma once

#include <JuceHeader.h>

#include "ThemeButton.h"

class Menu : public juce::Component
{
public:
    Menu();

    void resized() override;

    ThemeButton& getThemeButtonRef();

private:
    ThemeButton theme_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Menu)
};
