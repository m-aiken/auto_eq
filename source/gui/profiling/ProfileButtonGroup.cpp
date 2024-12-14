#include "ProfileButtonGroup.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
ProfileButtonGroup::ProfileButtonGroup()
    : group_label_("profile_button_group_label", "Profile:")
    , create_profile_button_("Create")
    , load_profile_button_("Load")
    , save_profile_button_("Save")
    , save_as_profile_button_("Save As")
{
    addAndMakeVisible(group_label_);
    addAndMakeVisible(create_profile_button_);
    addAndMakeVisible(load_profile_button_);
    addAndMakeVisible(save_profile_button_);
    addAndMakeVisible(save_as_profile_button_);
}

/*---------------------------------------------------------------------------
**
*/
void
ProfileButtonGroup::paint(juce::Graphics& g)
{
    juce::ignoreUnused(g);
    // g.setColour(Theme::getColour(Theme::SECTION_BORDER));
    // g.drawRect(getLocalBounds(), 1);

    // g.fillAll(Theme::getColour(Theme::SECTION_BORDER));
}

/*---------------------------------------------------------------------------
**
*/
void
ProfileButtonGroup::resized()
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
        Track(Fr(20)), Track(Fr(20)), Track(Fr(20)), Track(Fr(20)), Track(Fr(20)),
    };

    grid.items.add(juce::GridItem(group_label_));
    grid.items.add(juce::GridItem(create_profile_button_));
    grid.items.add(juce::GridItem(load_profile_button_));
    grid.items.add(juce::GridItem(save_profile_button_));
    grid.items.add(juce::GridItem(save_as_profile_button_));

    grid.setGap(Px(padding));

    grid.performLayout(grid_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
