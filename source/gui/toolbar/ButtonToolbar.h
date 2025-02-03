#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "CustomTextToggleButton.h"
#include "GlobalConstants.h"
#include "PluginEnablementButton.h"
#include "ReadonlyTextBox.h"
#include "ThemeButton.h"
#include "ToolbarSeparator.h"

class ButtonToolbar : public juce::Component
{
public:
    explicit ButtonToolbar(juce::AudioProcessorValueTreeState& apvts);

    void resized() override;

    PluginEnablementButton& getPluginEnablementButton();
    CustomTextToggleButton& getPowerSavingButton();
    CustomTextToggleButton& getAnalysisStateButton();
    ThemeButton&            getThemeButton();
    ReadonlyTextBox&        getCurrentPresetTextBox();

    [[nodiscard]] const std::unique_ptr< CustomTextButton >&
    getPresetButton(const PresetManagement::BUTTON_ID button_id) const;

    void setLoadedPresetName(const juce::String& name);
    void setGlobalEnablement(const bool enable);

private:
    PluginEnablementButton plugin_enablement_button_;
    CustomTextToggleButton power_saving_button_;
    CustomTextToggleButton analysis_state_button_;
    ReadonlyTextBox        current_profile_name_;
    ThemeButton            theme_button_;

    std::array< std::unique_ptr< CustomTextButton >, PresetManagement::NUM_BUTTONS > preset_management_buttons_;

    ToolbarSeparator section_separator_1_;
    ToolbarSeparator section_separator_2_;

    static constexpr int PADDING = 6;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonToolbar)
};
