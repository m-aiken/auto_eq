#include "ButtonToolbar.h"

/*---------------------------------------------------------------------------
**
*/
ButtonToolbar::ButtonToolbar(juce::AudioProcessorValueTreeState& apvts)
    : plugin_enablement_button_(apvts, GuiParams::POWER)
    , power_saving_button_(apvts, GuiParams::POWER_SAVING, GuiParams::INITIAL_POWER_SAVING_STATE, "Power Saving")
    , analysis_state_button_(apvts,
                             GuiParams::ANALYSE_INPUT,
                             GuiParams::INITIAL_ANALYSIS_STATE,
                             "Stop Analysis",
                             "Start Analysis")
    , current_profile_name_("unsaved preset...")
{
    for (int i = 0; i < PresetManagement::NUM_BUTTONS; ++i) {
        const auto&         button_id    = static_cast< PresetManagement::BUTTON_ID >(i);
        const juce::String& button_text  = PresetManagement::getButtonText(button_id);
        preset_management_buttons_.at(i) = std::make_unique< CustomTextButton >(button_text);

        addAndMakeVisible(preset_management_buttons_.at(i).get());
    }

    addAndMakeVisible(plugin_enablement_button_);
    addAndMakeVisible(power_saving_button_);
    addAndMakeVisible(analysis_state_button_);
    addAndMakeVisible(current_profile_name_);
    addAndMakeVisible(theme_button_);

    addAndMakeVisible(section_separator_1_);
    addAndMakeVisible(section_separator_2_);
}

/*---------------------------------------------------------------------------
**
*/
void
ButtonToolbar::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    using Px    = juce::Grid::Px;

    const auto bounds      = getLocalBounds();
    const auto grid_bounds = bounds.withSizeKeepingCentre(bounds.getWidth() - (PADDING * 2),
                                                          bounds.getHeight() - (PADDING * 2));

    juce::Grid grid;

    grid.autoRows = Track(Fr(100));

    grid.templateColumns = {
        Track(Fr(8)),   //! Plugin enablement button.
        Track(Fr(12)),  //! Start/Stop Analysis button.
        Track(Fr(6)),   //! ******************************** SECTION SEPARATOR 1.
        Track(Fr(6)),   //! "New" preset button.
        Track(Fr(24)),  //! Current preset name.
        Track(Fr(6)),   //! "Load" preset button.
        Track(Fr(6)),   //! "Save" preset button.
        Track(Fr(6)),   //! "Save As" preset button.
        Track(Fr(6)),   //! ******************************** SECTION SEPARATOR 2.
        Track(Fr(12)),  //! Power saving button.
        Track(Fr(8)),   //! Theme button.
    };

    grid.items.add(juce::GridItem(plugin_enablement_button_));
    grid.items.add(juce::GridItem(analysis_state_button_));
    grid.items.add(juce::GridItem(section_separator_1_));
    grid.items.add(juce::GridItem(preset_management_buttons_.at(PresetManagement::BUTTON_NEW).get()));
    grid.items.add(juce::GridItem(current_profile_name_));
    grid.items.add(juce::GridItem(preset_management_buttons_.at(PresetManagement::BUTTON_OPEN).get()));
    grid.items.add(juce::GridItem(preset_management_buttons_.at(PresetManagement::BUTTON_SAVE).get()));
    grid.items.add(juce::GridItem(preset_management_buttons_.at(PresetManagement::BUTTON_SAVE_AS).get()));
    grid.items.add(juce::GridItem(section_separator_2_));
    grid.items.add(juce::GridItem(power_saving_button_));
    grid.items.add(juce::GridItem(theme_button_));

    grid.setGap(Px(PADDING));

    grid.performLayout(grid_bounds);
}

/*---------------------------------------------------------------------------
**
*/
PluginEnablementButton&
ButtonToolbar::getPluginEnablementButton()
{
    return plugin_enablement_button_;
}

/*---------------------------------------------------------------------------
**
*/
CustomTextToggleButton&
ButtonToolbar::getPowerSavingButton()
{
    return power_saving_button_;
}

/*---------------------------------------------------------------------------
**
*/
CustomTextToggleButton&
ButtonToolbar::getAnalysisStateButton()
{
    return analysis_state_button_;
}

/*---------------------------------------------------------------------------
**
*/
ThemeButton&
ButtonToolbar::getThemeButton()
{
    return theme_button_;
}

/*---------------------------------------------------------------------------
**
*/
ReadonlyTextBox&
ButtonToolbar::getCurrentPresetTextBox()
{
    return current_profile_name_;
}

/*---------------------------------------------------------------------------
**
*/
const std::unique_ptr< CustomTextButton >&
ButtonToolbar::getPresetButton(const PresetManagement::BUTTON_ID button_id) const
{
    return preset_management_buttons_.at(button_id);
}

/*---------------------------------------------------------------------------
**
*/
void
ButtonToolbar::setLoadedPresetName(const juce::String& name)
{
    current_profile_name_.setText(name);
}

/*---------------------------------------------------------------------------
**
*/
void
ButtonToolbar::setGlobalEnablement(const bool enable)
{
    analysis_state_button_.setEnabled(enable);
    current_profile_name_.setEnabled(enable);
    power_saving_button_.setEnabled(enable);
    theme_button_.setEnabled(enable);

    section_separator_1_.setEnabled(enable);
    section_separator_2_.setEnabled(enable);

    for (auto& preset_btn : preset_management_buttons_) {
        preset_btn.get()->setEnabled(enable);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
