#pragma once

#include <JuceHeader.h>

#include "MeterDbScale.h"
#include "MeterGroup.h"
#include "MeterLabelGroup.h"
#include "PluginProcessor.h"

class MetersWidget : public juce::Component
{
public:
    explicit MetersWidget(PluginProcessor& p);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    MeterDbScale    db_scale_top_;
    MeterDbScale    db_scale_bottom_;
    MeterLabelGroup meter_labels_;
    MeterGroup      meters_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MetersWidget)
};
