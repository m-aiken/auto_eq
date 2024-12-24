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
    , toolbar_(p.getApvts())
    , filter_res_graph_(p)
    , profiler_widget_(p.getApvts(), p.getMonoWaveform())
    , eq_intensity_(p.getApvts())
    , master_gain_(p)
    , lufs_meters_(p)
    , cached_power_saving_state_(GuiParams::INITIAL_POWER_SAVING_STATE)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(toolbar_);
    addAndMakeVisible(filter_res_graph_);
    addAndMakeVisible(profiler_widget_);
    addAndMakeVisible(eq_intensity_);
    addAndMakeVisible(master_gain_);
    addAndMakeVisible(lufs_meters_);

    toolbar_.getPluginEnablementButton().addListener(this);
    toolbar_.getModeSelectorSwitch().addListener(this);
    toolbar_.getAnalysisStateButton().addListener(this);
    toolbar_.getThemeButton().addListener(this);
    lufs_meters_.getResetButton().addListener(this);

    setResizable(true, true);
    setResizeLimits(MAIN_WINDOW_MIN_WIDTH, MAIN_WINDOW_MIN_HEIGHT, MAIN_WINDOW_MAX_WIDTH, MAIN_WINDOW_MAX_HEIGHT);
    setSize(MAIN_WINDOW_MAX_WIDTH, MAIN_WINDOW_MAX_HEIGHT);
}

/*---------------------------------------------------------------------------
**
*/
PluginEditor::~PluginEditor()
{
    toolbar_.getPluginEnablementButton().removeListener(this);
    toolbar_.getModeSelectorSwitch().removeListener(this);
    toolbar_.getAnalysisStateButton().removeListener(this);
    toolbar_.getThemeButton().removeListener(this);
    lufs_meters_.getResetButton().removeListener(this);

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
    const juce::Rectangle< int > bounds                = getLocalBounds();
    const int                    bounds_height         = bounds.getHeight();
    const int                    bounds_width          = bounds.getWidth();
    const int                    top_controls_height   = static_cast< int >(std::floor(bounds_height * 0.05));
    const int                    graph_height          = static_cast< int >(std::floor(bounds_height * 0.65));
    const int                    bottom_section_height = static_cast< int >(std::floor(bounds_height * 0.25));
    const int                    eq_intensity_width    = static_cast< int >(std::floor(bounds_width * 0.15));
    const int                    master_gain_width     = static_cast< int >(std::floor(bounds_width * 0.15));
    const int                    meters_width          = static_cast< int >(std::floor(bounds_width * 0.7));
    const int                    bottom_section_y      = bounds.getBottom() - bottom_section_height;

    // Top button toolbar.
    toolbar_.setBounds(0, 0, bounds_width, top_controls_height);

    // EQ graph and profiler widget. They occupy the same space as their visibility is dependent on the mode.
    const juce::Rectangle< int > graph_bounds(0, top_controls_height, bounds_width, graph_height);

    filter_res_graph_.setBounds(graph_bounds);
    profiler_widget_.setBounds(graph_bounds);

    const bool profiler_mode = toolbar_.getModeSelectorSwitch().getToggleState();

    filter_res_graph_.setVisible(!profiler_mode);
    profiler_widget_.setVisible(profiler_mode);

    // Bottom section.
    eq_intensity_.setBounds(0, bottom_section_y, eq_intensity_width, bottom_section_height);
    master_gain_.setBounds(eq_intensity_.getRight(), bottom_section_y, master_gain_width, bottom_section_height);
    lufs_meters_.setBounds(master_gain_.getRight(), bottom_section_y, meters_width, bottom_section_height);
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

    const PluginEnablementButton& plugin_enablement_button = toolbar_.getPluginEnablementButton();
    const ToggleSwitch&           mode_selector_switch     = toolbar_.getModeSelectorSwitch();
    CustomTextToggleButton&       power_saving_button      = toolbar_.getPowerSavingButton();
    TransportButton&              analysis_state_button    = toolbar_.getAnalysisStateButton();
    const ThemeButton&            theme_button             = toolbar_.getThemeButton();
    const CustomTextButton&       lufs_meters_reset_button = lufs_meters_.getResetButton();

    if (button == &plugin_enablement_button) {
        const bool plugin_enabled = plugin_enablement_button.getToggleState();

        toolbar_.setGlobalEnablement(plugin_enabled);
        filter_res_graph_.setEnabled(plugin_enabled);
        eq_intensity_.setEnabled(plugin_enabled);
        master_gain_.setEnabled(plugin_enabled);
        lufs_meters_.setEnabled(plugin_enabled);

        // If the user is disabling the plugin and the analysis is active, stop the analysis.
        if (!plugin_enabled && analysis_state_button.getToggleState()) {
            analysis_state_button.setToggleState(false, juce::sendNotification);
        }

        // If the user is disabling the plugin and the FFT is being drawn, stop drawing it.
        // Preserve the state of the button though so that it's restored when the user re-enables the plugin.
        if (!plugin_enabled) {
            cached_power_saving_state_ = power_saving_button.getToggleState();

            power_saving_button.setToggleState(true, juce::sendNotification);
        }
        else {
            // The plugin is being re-enabled. Restore the FTT button state.
            power_saving_button.setToggleState(cached_power_saving_state_, juce::sendNotification);
        }

        repaint();
    }
    else if (button == &mode_selector_switch) {
        const bool profiler_mode = mode_selector_switch.getToggleState();

        filter_res_graph_.setVisible(!profiler_mode);
        profiler_widget_.setVisible(profiler_mode);

        power_saving_button.setEnabled(!profiler_mode);
    }
    else if (button == &analysis_state_button) {
        analysis_state_button.getToggleState() ? processor_ref_.startInputAnalysis() : processor_ref_.stopInputAnalysis();
    }
    else if (button == &theme_button) {
        repaint();
    }
    else if (button == &lufs_meters_reset_button) {
        processor_ref_.resetLufsModule();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
