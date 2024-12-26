#pragma once

#include <JuceHeader.h>

#include "CustomTextButton.h"
#include "DisableableLabel.h"
#include "LufsLabelGroup.h"
#include "LufsMeterGroup.h"
#include "MeterDbScale.h"
#include "PluginProcessor.h"

class LufsMetersWidget : public juce::Component
{
public:
    explicit LufsMetersWidget(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

    CustomTextButton& getResetButton();

private:
    DisableableLabel widget_label_;
    MeterDbScale     db_scale_top_;
    MeterDbScale     db_scale_bottom_;
    LufsLabelGroup   meter_labels_;
    LufsMeterGroup   meters_;
    CustomTextButton reset_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LufsMetersWidget)
};
