#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "CustomTextToggleButton.h"
#include "ModeSelector.h"
#include "PluginEnablementButton.h"
#include "ThemeButton.h"
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
    CustomTextButton       new_profile_button_;
    CustomTextButton       load_profile_button_;
    CustomTextButton       save_profile_button_;
    CustomTextButton       save_as_profile_button_;
    ThemeButton            theme_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonToolbar)
};
