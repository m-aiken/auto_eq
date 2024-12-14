#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "CustomTextButton.h"

class ProfileButtonGroup : public juce::TextButton
{
public:
    ProfileButtonGroup();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DisableableLabel group_label_;
    CustomTextButton create_profile_button_;
    CustomTextButton load_profile_button_;
    CustomTextButton save_profile_button_;
    CustomTextButton save_as_profile_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProfileButtonGroup)
};
