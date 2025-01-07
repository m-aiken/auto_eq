#pragma once

#include <JuceHeader.h>

#include "CustomLookAndFeel.h"
#include "PresetManager.h"

class PresetMenu : public juce::PopupMenu
{
public:
    PresetMenu(const PresetManager& preset_manager, CustomLookAndFeel& lnf);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetMenu)
};
