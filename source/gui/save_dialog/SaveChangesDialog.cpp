#include "SaveChangesDialog.h"

/*---------------------------------------------------------------------------
**
*/
SaveChangesDialog::SaveChangesDialog(PluginProcessor& processor_ref, ButtonToolbar& toolbar)
    : SaveDialogBase(processor_ref, toolbar, "Discard", "Save")
{
}

/*---------------------------------------------------------------------------
**
*/
void
SaveChangesDialog::buttonClicked(juce::Button* button)
{
    // Save the current settings if the user wants to.
    if (button == &positive_button_) {
        // We're either saving with the current name or saving as something else.
        const juce::String& name = name_entry_box_.getText();

        if (name == preset_manager_.getCurrentlyLoadedPresetName()) {
            preset_manager_.savePreset();
        }
        else {
            preset_manager_.savePresetAs(name);
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
