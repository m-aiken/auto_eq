#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "LufsLabelGroup.h"
#include "LufsMeterGroup.h"
#include "MeterDbScale.h"
#include "PluginProcessor.h"
#include "ResetButton.h"

class LufsMeterWidget : public juce::Component
{
public:
    explicit LufsMeterWidget(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DisableableLabel widget_label_;
    MeterDbScale     db_scale_top_;
    MeterDbScale     db_scale_bottom_;
    LufsLabelGroup   meter_labels_;
    LufsMeterGroup   meters_;
    ResetButton      reset_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LufsMeterWidget)
};
