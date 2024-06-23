#pragma once

#include "PluginProcessor.h"
#include "gui/CustomLookAndFeel.h"
#include "gui/intensity_control/IntensityControl.h"
#include "gui/menu/Menu.h"
#include "gui/meters/MeterGroup.h"
#include "gui/response_graph/FilterResponseGraph.h"

class PluginEditor final
    : public juce::AudioProcessorEditor
    , public juce::Button::Listener
{
public:
    explicit PluginEditor(PluginProcessor& p);
    ~PluginEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processor_ref_;

    Menu                menu_;
    FilterResponseGraph filter_res_graph_;
    IntensityControl    intensity_control_;
    MeterGroup          meter_group_;

    CustomLookAndFeel lnf_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
