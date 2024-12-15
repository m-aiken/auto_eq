#include "ButtonToolbar.h"

/*---------------------------------------------------------------------------
**
*/
ButtonToolbar::ButtonToolbar(juce::AudioProcessorValueTreeState& apvts)
    : plugin_enablement_button_(apvts, GuiParams::POWER)
    , spectrum_visibility_button_(apvts, GuiParams::SHOW_FFT)
    , analysis_state_button_(apvts, GuiParams::ANALYSE_INPUT)
    , profile_group_label_("profile_button_group_label", "Profiling:")
    , create_profile_button_("Create")
    , load_profile_button_("Load")
    , save_profile_button_("Save")
    , save_as_profile_button_("Save As")
{
    addAndMakeVisible(plugin_enablement_button_);
    addAndMakeVisible(spectrum_visibility_button_);
    addAndMakeVisible(analysis_state_button_);
    addAndMakeVisible(profile_group_label_);
    addAndMakeVisible(create_profile_button_);
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

    const int button_col_pct = 10;
    const int spacer_col_pct = 10;
    const int padding        = 6;
    auto      bounds         = getLocalBounds();
    auto      grid_bounds    = bounds.withSizeKeepingCentre(bounds.getWidth() - (padding * 2),
                                                    bounds.getHeight() - (padding * 2));

    juce::Grid grid;

    grid.autoRows = Track(Fr(100));

    grid.templateColumns = {
        Track(Fr(button_col_pct)),  //! Plugin enablement button.
        Track(Fr(button_col_pct)),  //! Spectrum visibility button.
        Track(Fr(button_col_pct)),  //! Analysis state button.
        Track(Fr(button_col_pct)),  //! Profile group label.
        Track(Fr(button_col_pct)),  //! "Create" profile button.
        Track(Fr(button_col_pct)),  //! "Load" profile button.
        Track(Fr(button_col_pct)),  //! "Save" profile button.
        Track(Fr(button_col_pct)),  //! "Save As" profile button.
        Track(Fr(spacer_col_pct)),  //! Spacer.
        Track(Fr(button_col_pct)),  //! Theme button.
    };

    grid.items.add(juce::GridItem(plugin_enablement_button_));
    grid.items.add(juce::GridItem(spectrum_visibility_button_));
    grid.items.add(juce::GridItem(analysis_state_button_));
    grid.items.add(juce::GridItem(profile_group_label_));
    grid.items.add(juce::GridItem(create_profile_button_));
    grid.items.add(juce::GridItem(load_profile_button_));
    grid.items.add(juce::GridItem(save_profile_button_));
    grid.items.add(juce::GridItem(save_as_profile_button_));
    grid.items.add(juce::GridItem());
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
SpectrumVisibilityButton&
ButtonToolbar::getSpectrumVisibilityButton()
{
    return spectrum_visibility_button_;
}

/*---------------------------------------------------------------------------
**
*/
AnalysisStateButton&
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
** End of File
*/
