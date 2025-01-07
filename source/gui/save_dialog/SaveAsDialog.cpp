#include "SaveAsDialog.h"

/*---------------------------------------------------------------------------
**
*/
SaveAsDialog::SaveAsDialog(PluginProcessor& processor_ref, ButtonToolbar& toolbar)
    : SaveDialogBase(processor_ref, toolbar, "Cancel", "Save")
{
}

/*---------------------------------------------------------------------------
**
*/
void
SaveAsDialog::buttonClicked(juce::Button* button)
{
    if (button == &positive_button_) {
        const int index = preset_manager_.savePresetAs(name_entry_box_.getText());

        if (index != PresetManager::INVALID_PRESET_INDEX) {
            if (processor_ref_.loadPreset(index)) {
                toolbar_.setLoadedPresetName(preset_manager_.getCurrentlyLoadedPresetName());
            }
        }
    }

    // Close the dialog window.
    if (auto* dw = findParentComponentOfClass< DialogWindow >()) {
        dw->exitModalState();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
