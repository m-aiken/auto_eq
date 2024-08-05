#pragma once

#include "PluginProcessor.h"
#include "gui/limiter/LimiterWidget.h"
#include "gui/look_and_feel/CustomLookAndFeel.h"
#include "gui/meters/MeterGroup.h"
#include "gui/response_graph/FilterResponseGraph.h"
#include "gui/widgets/MenuButton.h"
#include "gui/widgets/PowerButton.h"
#include "gui/widgets/RecordButton.h"
#include "gui/widgets/ThemeButton.h"

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

    PowerButton         power_button_;
    RecordButton        analyse_input_button_;
    MenuButton          show_fft_button_;
    ThemeButton         theme_button_;
    FilterResponseGraph filter_res_graph_;
    LimiterWidget       limiter_widget_;
    MeterGroup          meter_group_;

    CustomLookAndFeel lnf_;

    bool cached_fft_draw_status_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
