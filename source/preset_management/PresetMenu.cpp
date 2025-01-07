#include "PresetMenu.h"

/*---------------------------------------------------------------------------
**
*/
PresetMenu::PresetMenu(const PresetManager& preset_manager, CustomLookAndFeel& lnf)
{
    setLookAndFeel(&lnf);

    const ValueTree& presets = preset_manager.getPresets();

    for (int i = PresetManager::FIRST_USER_DEFINED_PRESET_INDEX; i < presets.getNumChildren(); ++i) {
        const juce::ValueTree preset = presets.getChild(i);
        juce::PopupMenu::Item item;

        item.itemID = (i + 1);
        item.text   = preset.getProperty(PresetManager::PROPERTY_IDENTIFIER_NAME).toString();

        addItem(item);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
