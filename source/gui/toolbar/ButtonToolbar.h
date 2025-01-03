#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "CustomTextToggleButton.h"
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

    void setGlobalEnablement(const bool enable);

private:
    PluginEnablementButton plugin_enablement_button_;
    CustomTextToggleButton power_saving_button_;
    CustomTextToggleButton analysis_state_button_;
    ReadonlyTextBox        current_profile_name_;
    CustomTextButton       new_profile_button_;
    CustomTextButton       load_profile_button_;
    CustomTextButton       save_profile_button_;
    CustomTextButton       save_as_profile_button_;
    ThemeButton            theme_button_;

    ToolbarSeparator section_separator_1_;
    ToolbarSeparator section_separator_2_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonToolbar)
};
