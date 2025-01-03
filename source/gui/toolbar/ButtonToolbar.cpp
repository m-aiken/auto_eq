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
    , current_profile_name_("Unsaved")
    , new_profile_button_("New")
    , load_profile_button_("Open")
    , save_profile_button_("Save")
    , save_as_profile_button_("Save As")
{
    addAndMakeVisible(plugin_enablement_button_);
    addAndMakeVisible(power_saving_button_);
    addAndMakeVisible(analysis_state_button_);
    addAndMakeVisible(current_profile_name_);
    addAndMakeVisible(new_profile_button_);
    addAndMakeVisible(load_profile_button_);
    addAndMakeVisible(save_profile_button_);
    addAndMakeVisible(save_as_profile_button_);
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

    const int padding     = 6;
    auto      bounds      = getLocalBounds();
    auto      grid_bounds = bounds.withSizeKeepingCentre(bounds.getWidth() - (padding * 2),
                                                    bounds.getHeight() - (padding * 2));

    juce::Grid grid;

    grid.autoRows = Track(Fr(100));

    grid.templateColumns = {
        Track(Fr(8)),   //! Plugin enablement button.
        Track(Fr(12)),  //! Start/Stop Analysis button.
        Track(Fr(6)),   //! ******************************** SECTION SEPARATOR 1.
        Track(Fr(24)),  //! Current profile name.
        Track(Fr(6)),   //! "New" profile button.
        Track(Fr(6)),   //! "Load" profile button.
        Track(Fr(6)),   //! "Save" profile button.
        Track(Fr(6)),   //! "Save As" profile button.
        Track(Fr(6)),   //! ******************************** SECTION SEPARATOR 2.
        Track(Fr(12)),  //! Power saving button.
        Track(Fr(8)),   //! Theme button.
    };

    grid.items.add(juce::GridItem(plugin_enablement_button_));
    grid.items.add(juce::GridItem(analysis_state_button_));
    grid.items.add(juce::GridItem(section_separator_1_));
    grid.items.add(juce::GridItem(current_profile_name_));
    grid.items.add(juce::GridItem(new_profile_button_));
    grid.items.add(juce::GridItem(load_profile_button_));
    grid.items.add(juce::GridItem(save_profile_button_));
    grid.items.add(juce::GridItem(save_as_profile_button_));
    grid.items.add(juce::GridItem(section_separator_2_));
    grid.items.add(juce::GridItem(power_saving_button_));
    grid.items.add(juce::GridItem(theme_button_));

    grid.setGap(Px(padding));

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
void
ButtonToolbar::setGlobalEnablement(const bool enable)
{
    analysis_state_button_.setEnabled(enable);
    current_profile_name_.setEnabled(enable);
    new_profile_button_.setEnabled(enable);
    load_profile_button_.setEnabled(enable);
    save_profile_button_.setEnabled(enable);
    save_as_profile_button_.setEnabled(enable);
    power_saving_button_.setEnabled(enable);
    theme_button_.setEnabled(enable);

    section_separator_1_.setEnabled(enable);
    section_separator_2_.setEnabled(enable);
}

/*---------------------------------------------------------------------------
** End of File
*/
