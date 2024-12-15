#pragma once

#include <JuceHeader.h>

#include "AnalysisStateButton.h"
#include "DisableableLabel.h"
#include "CustomTextButton.h"
#include "PluginEnablementButton.h"
#include "SpectrumVisibilityButton.h"
#include "ThemeButton.h"

class ButtonToolbar : public juce::Component
{
public:
    explicit ButtonToolbar(juce::AudioProcessorValueTreeState& apvts);

    void resized() override;

    PluginEnablementButton&   getPluginEnablementButton();
    SpectrumVisibilityButton& getSpectrumVisibilityButton();
    AnalysisStateButton&      getAnalysisStateButton();
    ThemeButton&              getThemeButton();

private:
    PluginEnablementButton   plugin_enablement_button_;
    SpectrumVisibilityButton spectrum_visibility_button_;
    AnalysisStateButton      analysis_state_button_;
    DisableableLabel         profile_group_label_;
    CustomTextButton         create_profile_button_;
    CustomTextButton         load_profile_button_;
    CustomTextButton         save_profile_button_;
    CustomTextButton         save_as_profile_button_;
    ThemeButton              theme_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonToolbar)
};
