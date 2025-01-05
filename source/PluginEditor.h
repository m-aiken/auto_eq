#pragma once

#include "ButtonToolbar.h"
#include "CustomLookAndFeel.h"
#include "EqIntensity.h"
#include "FilterResponseGraph.h"
#include "InputTrim.h"
#include "MetersWidget.h"
#include "MasterGain.h"
#include "PluginProcessor.h"

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
    static const uint16 MAIN_WINDOW_MIN_WIDTH;
    static const uint16 MAIN_WINDOW_MIN_HEIGHT;
    static const uint16 MAIN_WINDOW_MAX_WIDTH;
    static const uint16 MAIN_WINDOW_MAX_HEIGHT;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processor_ref_;

    ButtonToolbar       toolbar_;
    FilterResponseGraph filter_res_graph_;
    InputTrim           input_trim_;
    EqIntensity         eq_intensity_;
    MasterGain          master_gain_;
    MetersWidget        meters_;

    CustomLookAndFeel lnf_;

    bool cached_power_saving_state_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
