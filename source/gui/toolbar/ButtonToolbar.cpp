#include "ButtonToolbar.h"

/*---------------------------------------------------------------------------
**
*/
ButtonToolbar::ButtonToolbar(juce::AudioProcessorValueTreeState& apvts)
    : plugin_enablement_button_(apvts, GuiParams::POWER)
    , mode_selector_(apvts)
    , power_saving_button_(apvts, GuiParams::POWER_SAVING, "Power Saving", GuiParams::INITIAL_POWER_SAVING_STATE)
    , transport_(apvts)
    , current_profile_name_("Unsaved")
    , new_profile_button_("N")
    , load_profile_button_("O")
    , save_profile_button_("S")
    , save_as_profile_button_("S/A")
{
    addAndMakeVisible(plugin_enablement_button_);
    addAndMakeVisible(mode_selector_);
    addAndMakeVisible(power_saving_button_);
    addAndMakeVisible(transport_);
    addAndMakeVisible(current_profile_name_);
    addAndMakeVisible(new_profile_button_);
    addAndMakeVisible(load_profile_button_);
    addAndMakeVisible(save_profile_button_);
    addAndMakeVisible(save_as_profile_button_);
    addAndMakeVisible(theme_button_);

    addAndMakeVisible(section_separator_1_);
    addAndMakeVisible(section_separator_2_);
    addAndMakeVisible(section_separator_3_);
    addAndMakeVisible(section_separator_4_);
    addAndMakeVisible(section_separator_5_);
    addAndMakeVisible(section_separator_6_);
    addAndMakeVisible(section_separator_7_);
    addAndMakeVisible(section_separator_8_);
    addAndMakeVisible(section_separator_9_);
    addAndMakeVisible(section_separator_10_);
    addAndMakeVisible(section_separator_11_);
    addAndMakeVisible(section_separator_12_);
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
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 1.
        Track(Fr(16)),  //! Mode selector switch.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 2.
        Track(Fr(24)),  //! Current profile name.
        Track(Fr(2)),   //! "New" profile button.
        Track(Fr(2)),   //! "Load" profile button.
        Track(Fr(2)),   //! "Save" profile button.
        Track(Fr(2)),   //! "Save As" profile button.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 3.
        Track(Fr(16)),  //! Transport button.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 4.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 5.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 6.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 7.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 8.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 9.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 10.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 11.
        Track(Fr(8)),   //! Power saving button.
        Track(Fr(1)),   //! ******************************** SECTION SEPARATOR 12.
        Track(Fr(8)),   //! Theme button.
    };

    grid.items.add(juce::GridItem(plugin_enablement_button_));
    grid.items.add(juce::GridItem(section_separator_1_));
    grid.items.add(juce::GridItem(mode_selector_));
    grid.items.add(juce::GridItem(section_separator_2_));
    grid.items.add(juce::GridItem(current_profile_name_));
    grid.items.add(juce::GridItem(new_profile_button_));
    grid.items.add(juce::GridItem(load_profile_button_));
    grid.items.add(juce::GridItem(save_profile_button_));
    grid.items.add(juce::GridItem(save_as_profile_button_));
    grid.items.add(juce::GridItem(section_separator_3_));
    grid.items.add(juce::GridItem(transport_));
    grid.items.add(juce::GridItem(section_separator_4_));
    grid.items.add(juce::GridItem(section_separator_5_));
    grid.items.add(juce::GridItem(section_separator_6_));
    grid.items.add(juce::GridItem(section_separator_7_));
    grid.items.add(juce::GridItem(section_separator_8_));
    grid.items.add(juce::GridItem(section_separator_9_));
    grid.items.add(juce::GridItem(section_separator_10_));
    grid.items.add(juce::GridItem(section_separator_11_));
    grid.items.add(juce::GridItem(power_saving_button_));
    grid.items.add(juce::GridItem(section_separator_12_));
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
ToggleSwitch&
ButtonToolbar::getModeSelectorSwitch()
{
    return mode_selector_.getToggleSwitch();
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
TransportButton&
ButtonToolbar::getAnalysisStateButton()
{
    return transport_.getButton();
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
    mode_selector_.setEnabled(enable);
    transport_.setEnabled(enable);
    current_profile_name_.setEnabled(enable);
    new_profile_button_.setEnabled(enable);
    load_profile_button_.setEnabled(enable);
    save_profile_button_.setEnabled(enable);
    save_as_profile_button_.setEnabled(enable);
    theme_button_.setEnabled(enable);

    section_separator_1_.setEnabled(enable);
    section_separator_2_.setEnabled(enable);
    section_separator_3_.setEnabled(enable);
    section_separator_4_.setEnabled(enable);
    section_separator_5_.setEnabled(enable);
    section_separator_6_.setEnabled(enable);
    section_separator_7_.setEnabled(enable);
    section_separator_8_.setEnabled(enable);
    section_separator_9_.setEnabled(enable);
    section_separator_10_.setEnabled(enable);
    section_separator_11_.setEnabled(enable);
    section_separator_12_.setEnabled(enable);

    // The power saving button only applies to the Analyser.
    const bool in_analyser_mode = !getModeSelectorSwitch().getToggleState();

    power_saving_button_.setEnabled(enable && in_analyser_mode);
}

/*---------------------------------------------------------------------------
** End of File
*/
