#include "ButtonToolbar.h"

/*---------------------------------------------------------------------------
**
*/
ButtonToolbar::ButtonToolbar(juce::AudioProcessorValueTreeState& apvts)
    : plugin_enablement_button_(apvts, GuiParams::POWER)
    , power_saving_button_(apvts, GuiParams::POWER_SAVING, "Power Saving", GuiParams::INITIAL_POWER_SAVING_STATE)
    , transport_(apvts)
    , load_profile_button_("Load")
    , save_profile_button_("Save")
    , save_as_profile_button_("Save As")
{
    addAndMakeVisible(plugin_enablement_button_);
    addAndMakeVisible(mode_selector_);
    addAndMakeVisible(power_saving_button_);
    addAndMakeVisible(transport_);
    addAndMakeVisible(load_profile_button_);
    addAndMakeVisible(save_profile_button_);
    addAndMakeVisible(save_as_profile_button_);
    addAndMakeVisible(theme_button_);
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
        Track(Fr(10)),  //! Plugin enablement button.
        Track(Fr(20)),  //! Mode selector switch.
        Track(Fr(10)),  //! Power saving button.
        Track(Fr(10)),  //! Empty space.
        Track(Fr(10)),  //! Transport button.
        Track(Fr(10)),  //! Empty space.
        Track(Fr(10)),  //! "Load" profile button.
        Track(Fr(10)),  //! "Save" profile button.
        Track(Fr(10)),  //! "Save As" profile button.
        Track(Fr(10)),  //! Theme button.
    };

    grid.items.add(juce::GridItem(plugin_enablement_button_));
    grid.items.add(juce::GridItem(mode_selector_));
    grid.items.add(juce::GridItem(power_saving_button_));
    grid.items.add(juce::GridItem());
    grid.items.add(juce::GridItem(transport_));
    grid.items.add(juce::GridItem());
    grid.items.add(juce::GridItem(load_profile_button_));
    grid.items.add(juce::GridItem(save_profile_button_));
    grid.items.add(juce::GridItem(save_as_profile_button_));
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
    load_profile_button_.setEnabled(enable);
    save_profile_button_.setEnabled(enable);
    save_as_profile_button_.setEnabled(enable);
    theme_button_.setEnabled(enable);

    // The power saving button only applies to the Analyser.
    const bool in_analyser_mode = !getModeSelectorSwitch().getToggleState();

    power_saving_button_.setEnabled(enable && in_analyser_mode);
}

/*---------------------------------------------------------------------------
** End of File
*/
