#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "CustomTextToggleButton.h"
#include "DisableableLabel.h"
#include "ModeSelector.h"
#include "PluginEnablementButton.h"
#include "ReadonlyTextBox.h"
#include "ThemeButton.h"
#include "ToolbarSeparator.h"
#include "TransportGroup.h"

class ButtonToolbar : public juce::Component
{
public:
    explicit ButtonToolbar(juce::AudioProcessorValueTreeState& apvts);

    void resized() override;

    PluginEnablementButton& getPluginEnablementButton();
    ToggleSwitch&           getModeSelectorSwitch();
    CustomTextToggleButton& getPowerSavingButton();
    TransportButton&        getAnalysisStateButton();
    ThemeButton&            getThemeButton();

    void setGlobalEnablement(const bool enable);

private:
    PluginEnablementButton plugin_enablement_button_;
    ModeSelector           mode_selector_;
    CustomTextToggleButton power_saving_button_;
    TransportGroup         transport_;
    ReadonlyTextBox        current_profile_name_;
    CustomTextButton       new_profile_button_;
    CustomTextButton       load_profile_button_;
    CustomTextButton       save_profile_button_;
    CustomTextButton       save_as_profile_button_;
    ThemeButton            theme_button_;

    ToolbarSeparator section_separator_1_;
    ToolbarSeparator section_separator_2_;
    ToolbarSeparator section_separator_3_;
    ToolbarSeparator section_separator_4_;
    ToolbarSeparator section_separator_5_;
    ToolbarSeparator section_separator_6_;
    ToolbarSeparator section_separator_7_;
    ToolbarSeparator section_separator_8_;
    ToolbarSeparator section_separator_9_;
    ToolbarSeparator section_separator_10_;
    ToolbarSeparator section_separator_11_;
    ToolbarSeparator section_separator_12_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonToolbar)
};
