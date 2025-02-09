#pragma once

#include <JuceHeader.h>

#include "ButtonToolbar.h"
#include "CustomTextButton.h"
#include "CustomTextEntryBox.h"
#include "PluginProcessor.h"
#include "PresetManager.h"
#include "WarningLabel.h"

class SaveDialogBase
    : public juce::Component
    , public juce::Button::Listener
{
public:
    SaveDialogBase(PluginProcessor&    processor_ref,
                   ButtonToolbar&      toolbar,
                   const juce::String& negative_button_text,
                   const juce::String& positive_button_text);

    ~SaveDialogBase() override;

    void resized() override;
    void buttonClicked(juce::Button* button) override = 0;

protected:
    void updatePositiveButtonEnablement();
    void updateDuplicateWarningVisibility();

    PluginProcessor& processor_ref_;
    PresetManager&   preset_manager_;
    ButtonToolbar&   toolbar_;

    CustomTextEntryBox name_entry_box_;
    CustomTextButton   negative_button_;
    CustomTextButton   positive_button_;
    WarningLabel       duplicate_warning_;

    static constexpr int PADDING = 24;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SaveDialogBase)
};
