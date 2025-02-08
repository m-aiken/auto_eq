#include "GlobalConstants.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PresetMenu.h"
#include "SaveAsDialog.h"
#include "SaveChangesDialog.h"
#include "Theme.h"

/*static*/ const uint16 PluginEditor::MAIN_WINDOW_MIN_WIDTH  = 900;
/*static*/ const uint16 PluginEditor::MAIN_WINDOW_MIN_HEIGHT = 500;
/*static*/ const uint16 PluginEditor::MAIN_WINDOW_MAX_WIDTH  = 1100;
/*static*/ const uint16 PluginEditor::MAIN_WINDOW_MAX_HEIGHT = 600;

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , preset_manager_(p.getPresetManager())
    , toolbar_(p.getApvts())
    , filter_res_graph_(p)
    , input_trim_(p.getApvts())
    , eq_intensity_(p.getApvts())
    , master_gain_(p)
    , meters_(p)
    , cached_power_saving_state_(GuiParams::INITIAL_POWER_SAVING_STATE)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(toolbar_);
    addAndMakeVisible(filter_res_graph_);
    addAndMakeVisible(input_trim_);
    addAndMakeVisible(eq_intensity_);
    addAndMakeVisible(master_gain_);
    addAndMakeVisible(meters_);

    toolbar_.getPluginEnablementButton().addListener(this);
    toolbar_.getAnalysisStateButton().addListener(this);
    toolbar_.getThemeButton().addListener(this);

    for (int i = 0; i < PresetManagement::NUM_BUTTONS; ++i) {
        toolbar_.getPresetButton(static_cast< PresetManagement::BUTTON_ID >(i)).get()->addListener(this);
    }

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
    toolbar_.getAnalysisStateButton().removeListener(this);
    toolbar_.getThemeButton().removeListener(this);

    for (int i = 0; i < PresetManagement::NUM_BUTTONS; ++i) {
        toolbar_.getPresetButton(static_cast< PresetManagement::BUTTON_ID >(i)).get()->removeListener(this);
    }

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
    const juce::Rectangle< int >& bounds                = getLocalBounds();
    const int                     bounds_height         = bounds.getHeight();
    const int                     bounds_width          = bounds.getWidth();
    const int                     top_controls_height   = static_cast< int >(std::floor(bounds_height * 0.05));
    const int                     graph_height          = static_cast< int >(std::floor(bounds_height * 0.65));
    const int                     bottom_section_height = static_cast< int >(std::floor(bounds_height * 0.25));
    const int                     rotary_widget_width   = static_cast< int >(std::floor(bounds_width * 0.15));
    const int                     meters_width          = static_cast< int >(std::floor(bounds_width * 0.55));
    const int                     bottom_section_y      = bounds.getBottom() - bottom_section_height;

    // Top button toolbar.
    toolbar_.setBounds(0, 0, bounds_width, top_controls_height);

    // EQ graph.
    filter_res_graph_.setBounds(0, top_controls_height, bounds_width, graph_height);

    // Bottom section.
    input_trim_.setBounds(0, bottom_section_y, rotary_widget_width, bottom_section_height);
    eq_intensity_.setBounds(input_trim_.getRight(), bottom_section_y, rotary_widget_width, bottom_section_height);
    master_gain_.setBounds(eq_intensity_.getRight(), bottom_section_y, rotary_widget_width, bottom_section_height);
    meters_.setBounds(master_gain_.getRight(), bottom_section_y, meters_width, bottom_section_height);
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
    CustomTextToggleButton&       power_saving_button      = toolbar_.getPowerSavingButton();
    CustomTextToggleButton&       analysis_state_button    = toolbar_.getAnalysisStateButton();
    const ThemeButton&            theme_button             = toolbar_.getThemeButton();

    typedef const std::unique_ptr< CustomTextButton > PresetButton;
    PresetButton& new_preset_button     = toolbar_.getPresetButton(PresetManagement::BUTTON_NEW);
    PresetButton& open_preset_button    = toolbar_.getPresetButton(PresetManagement::BUTTON_OPEN);
    PresetButton& save_preset_button    = toolbar_.getPresetButton(PresetManagement::BUTTON_SAVE);
    PresetButton& save_as_preset_button = toolbar_.getPresetButton(PresetManagement::BUTTON_SAVE_AS);

    if (button == &plugin_enablement_button) {
        const bool plugin_enabled = plugin_enablement_button.getToggleState();

        toolbar_.setGlobalEnablement(plugin_enabled);
        filter_res_graph_.setEnabled(plugin_enabled);
        input_trim_.setEnabled(plugin_enabled);
        eq_intensity_.setEnabled(plugin_enabled);
        master_gain_.setEnabled(plugin_enabled);
        meters_.setEnabled(plugin_enabled);

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
    else if (button == &analysis_state_button) {
        analysis_state_button.getToggleState() ? processor_ref_.startInputAnalysis() : processor_ref_.stopInputAnalysis();
    }
    else if (button == &theme_button) {
        repaint();
    }
    else if (button == new_preset_button.get()) {
        if (preset_manager_.currentPresetIsUnchangedDefault()) {
            // Nothing to do.
            return;
        }

        if (preset_manager_.currentPresetHasUnsavedChanges()) {
            handlePresetSaveChanges(PresetManager::OPERATION::NEW);
            // The callback from the "Save Changes" dialog being closed will call PluginEditor::handleLoadDefaultPreset().
            return;
        }

        handleLoadDefaultPreset();
    }
    else if (button == open_preset_button.get()) {
        if (preset_manager_.currentPresetHasUnsavedChanges()) {
            handlePresetSaveChanges(PresetManager::OPERATION::LOAD);
            // The callback from the "Save Changes" dialog being closed will call PluginEditor::handleDisplayPresetList().
            return;
        }

        handleDisplayPresetList();
    }
    else if (button == save_preset_button.get()) {
        if (!preset_manager_.currentPresetIsUnchangedDefault()) {
            preset_manager_.currentPresetHasDefaultName() ? handlePresetSaveAs() : handlePresetSave();
        }
    }
    else if (button == save_as_preset_button.get()) {
        handlePresetSaveAs();
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::handlePresetSave() const
{
    preset_manager_.savePreset();
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::handlePresetSaveAs()
{
    juce::DialogWindow::LaunchOptions dialog;
    const ComponentDimensions&        dims = getDialogDimensions();

    dialog.dialogTitle             = "Save As";
    dialog.dialogBackgroundColour  = Theme::getColour(Theme::MAIN_BG);
    dialog.componentToCentreAround = &filter_res_graph_;
    dialog.content.setOwned(new SaveAsDialog(processor_ref_, toolbar_));
    dialog.content->setLookAndFeel(&lnf_);
    dialog.content->setSize(dims.width_, dims.height_);
    dialog.launchAsync();
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::handlePresetSaveChanges(const PresetManager::OPERATION operation)
{
    juce::DialogWindow::LaunchOptions dialog;
    const ComponentDimensions&        dims = getDialogDimensions();

    dialog.dialogTitle             = "Save Changes?";
    dialog.dialogBackgroundColour  = Theme::getColour(Theme::MAIN_BG);
    dialog.componentToCentreAround = &filter_res_graph_;
    dialog.content.setOwned(new SaveChangesDialog(processor_ref_, toolbar_));
    dialog.content->setLookAndFeel(&lnf_);
    dialog.content->setSize(dims.width_, dims.height_);

    juce::DialogWindow*                    window   = dialog.launchAsync();
    juce::ModalComponentManager::Callback* callback = nullptr;

    switch (operation) {
    case PresetManager::OPERATION::NEW:
        callback = juce::ModalCallbackFunction::create([&](int ignore) { handleLoadDefaultPreset(); });
        break;

    case PresetManager::OPERATION::LOAD:
        callback = juce::ModalCallbackFunction::create([&](int ignore) { handleDisplayPresetList(); });
        break;

    case PresetManager::OPERATION::SAVE:
    case PresetManager::OPERATION::SAVE_AS:
    default:
        break;
    }

    if (callback != nullptr) {
        juce::ModalComponentManager::getInstance()->attachCallback(window, callback);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::handleLoadDefaultPreset()
{
    // Load the default empty preset.
    if (processor_ref_.loadPreset(PresetManager::DEFAULT_PRESET_INDEX)) {
        toolbar_.setLoadedPresetName(PresetManager::DEFAULT_PRESET_NAME);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::handleDisplayPresetList()
{
    // Launch dialog that lists the existing presets.
    PresetMenu       menu(preset_manager_, lnf_);
    ReadonlyTextBox& current_preset_text_box = toolbar_.getCurrentPresetTextBox();

    menu.showMenuAsync(PopupMenu::Options()
                           .withTargetComponent(current_preset_text_box)
                           .withMinimumWidth(current_preset_text_box.getWidth())
                           .withParentComponent(getParentComponent()),
                       [&](const int result) {
                           if (result < 1) {
                               return;
                           }

                           const int preset_index = (result - 1);

                           if (processor_ref_.loadPreset(preset_index)) {
                               current_preset_text_box.setText(preset_manager_.getCurrentlyLoadedPresetName());
                           }
                       });
}

/*---------------------------------------------------------------------------
**
*/
PluginEditor::ComponentDimensions
PluginEditor::getDialogDimensions() const
{
    ComponentDimensions dims;

    dims.width_  = static_cast< int >(std::floor(getLocalBounds().getWidth() * 0.3));
    dims.height_ = static_cast< int >(std::floor(getLocalBounds().getHeight() * 0.2));

    return dims;
}

/*---------------------------------------------------------------------------
** End of File
*/
