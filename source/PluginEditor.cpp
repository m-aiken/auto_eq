#include "GlobalConstants.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Theme.h"

/*static*/ const uint16 PluginEditor::MAIN_WINDOW_MIN_WIDTH  = 768;
/*static*/ const uint16 PluginEditor::MAIN_WINDOW_MIN_HEIGHT = 400;
/*static*/ const uint16 PluginEditor::MAIN_WINDOW_MAX_WIDTH  = 1100;
/*static*/ const uint16 PluginEditor::MAIN_WINDOW_MAX_HEIGHT = 600;

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , power_button_(p.getApvts(), GuiParams::POWER)
    , analyse_input_button_("Analyse Input", p.getApvts(), GuiParams::ANALYSE_INPUT)
    , show_fft_button_("Show Spectrum", p.getApvts(), GuiParams::SHOW_FFT)
    , unity_gain_button_("Unity Gain", p.getApvts(), GuiParams::UNITY_GAIN_ENABLED)
    , theme_button_()
    , filter_res_graph_(p)
    , meter_group_(p)
    , cached_fft_draw_status_(GuiParams::INITIAL_FFT_STATE)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(power_button_);
    addAndMakeVisible(analyse_input_button_);
    addAndMakeVisible(show_fft_button_);
    addAndMakeVisible(unity_gain_button_);
    addAndMakeVisible(theme_button_);
    addAndMakeVisible(filter_res_graph_);
    addAndMakeVisible(master_gain_);
    addAndMakeVisible(meter_group_);

    power_button_.addListener(this);
    analyse_input_button_.addListener(this);
    theme_button_.addListener(this);

    setResizable(true, true);
    setResizeLimits(MAIN_WINDOW_MIN_WIDTH, MAIN_WINDOW_MIN_HEIGHT, MAIN_WINDOW_MAX_WIDTH, MAIN_WINDOW_MAX_HEIGHT);
    setSize(MAIN_WINDOW_MAX_WIDTH, MAIN_WINDOW_MAX_HEIGHT);
}

/*---------------------------------------------------------------------------
**
*/
PluginEditor::~PluginEditor()
{
    power_button_.removeListener(this);
    analyse_input_button_.removeListener(this);
    theme_button_.removeListener(this);

    setLookAndFeel(nullptr);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(Theme::getColour(Theme::MAIN_BG));
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::resized()
{
    juce::Rectangle< int > bounds                  = getLocalBounds();
    int                    bounds_height           = bounds.getHeight();
    int                    bounds_width            = bounds.getWidth();
    int                    top_controls_height     = static_cast< int >(std::floor(bounds_height * 0.05));
    int                    analysis_button_width   = static_cast< int >(std::floor(bounds_width * 0.2));
    int                    fft_button_width        = static_cast< int >(std::floor(bounds_width * 0.2));
    int                    unity_gain_button_width = static_cast< int >(std::floor(bounds_width * 0.2));
    int                    theme_button_width      = static_cast< int >(std::floor(bounds_width * 0.1));
    int                    graph_height            = static_cast< int >(std::floor(bounds_height * 0.65));
    int                    bottom_section_height   = static_cast< int >(std::floor(bounds_height * 0.25));
    int                    master_gain_width       = static_cast< int >(std::floor(bounds_width * 0.25));
    int                    meters_width            = static_cast< int >(std::floor(bounds_width * 0.75));

    power_button_.setBounds(0, 0, top_controls_height, top_controls_height);
    analyse_input_button_.setBounds(analysis_button_width, 0, analysis_button_width, top_controls_height);
    show_fft_button_.setBounds(analyse_input_button_.getRight(), 0, fft_button_width, top_controls_height);
    unity_gain_button_.setBounds(show_fft_button_.getRight(), 0, unity_gain_button_width, top_controls_height);
    theme_button_.setBounds(bounds.getRight() - theme_button_width, 0, theme_button_width, top_controls_height);
    filter_res_graph_.setBounds(0, top_controls_height, bounds_width, graph_height);
    master_gain_.setBounds(0, bounds.getBottom() - bottom_section_height, master_gain_width, bottom_section_height);
    meter_group_.setBounds(master_gain_width,
                           bounds.getBottom() - bottom_section_height,
                           meters_width,
                           bottom_section_height);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::buttonClicked(juce::Button* button)
{
    if (button == nullptr) {
        return;
    }

    if (button == &power_button_) {
        bool plugin_enabled = power_button_.getToggleState();

        analyse_input_button_.setEnabled(plugin_enabled);
        show_fft_button_.setEnabled(plugin_enabled);
        filter_res_graph_.setEnabled(plugin_enabled);
        unity_gain_button_.setEnabled(plugin_enabled);
        master_gain_.setEnabled(plugin_enabled);
        meter_group_.setEnabled(plugin_enabled);

        // If the user is disabling the plugin and the analysis is active, stop the analysis.
        if (!plugin_enabled && analyse_input_button_.getToggleState()) {
            analyse_input_button_.setToggleState(false, juce::sendNotification);
        }

        // If the user is disabling the plugin and the FFT is being drawn, stop drawing it.
        // Preserve the state of the button though so that it's restored when the user re-enables the plugin.
        if (!plugin_enabled) {
            cached_fft_draw_status_ = show_fft_button_.getToggleState();

            show_fft_button_.setToggleState(false, juce::sendNotification);
        }
        else {
            // The plugin is being re-enabled. Restore the FTT button state.
            show_fft_button_.setToggleState(cached_fft_draw_status_, juce::sendNotification);
        }

        repaint();
    }
    else if (button == &analyse_input_button_) {
        analyse_input_button_.getToggleState() ? processor_ref_.startInputAnalysis() : processor_ref_.stopInputAnalysis();
    }
    else if (button == &theme_button_) {
        repaint();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
