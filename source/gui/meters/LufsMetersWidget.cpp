#include "GlobalConstants.h"
#include "LufsMetersWidget.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
LufsMetersWidget::LufsMetersWidget(PluginProcessor& p)
    : widget_label_("lufs_meters_widget_label", "LUFS")
    , meters_(p)
    , reset_button_("Reset")
{
    addAndMakeVisible(widget_label_);
    addAndMakeVisible(db_scale_top_);
    addAndMakeVisible(db_scale_bottom_);
    addAndMakeVisible(meter_labels_);
    addAndMakeVisible(meters_);
    addAndMakeVisible(reset_button_);
}

/*---------------------------------------------------------------------------
**
*/
void
LufsMetersWidget::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds());
#endif

    g.setColour(Theme::getColour(Theme::SECTION_BORDER));
    g.drawRect(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
LufsMetersWidget::resized()
{
    const juce::Rectangle< int > bounds              = getLocalBounds();
    const int                    bounds_width        = bounds.getWidth();
    const int                    bounds_height       = bounds.getHeight();
    const int                    label_section_width = static_cast< int >(std::floor(bounds_width * 0.15));
    const int                    meter_section_width = static_cast< int >(std::floor(bounds_width * 0.7));
    const int                    reset_button_width  = static_cast< int >(std::floor(bounds_width * 0.15));

    const int meter_section_x    = label_section_width;
    const int db_scale_height    = static_cast< int >(std::floor(bounds_height * 0.2));
    const int meter_group_height = static_cast< int >(std::floor(bounds_height * 0.6));
    const int meter_group_width  = static_cast< int >(std::floor(meter_section_width - (Global::METER_X_PADDING * 2)));
    const int label_group_height = meter_group_height;

    // Shift the labels left a bit to account for the padding around the meters.
    // They're too far away otherwise.
    const int label_group_x = static_cast< int >(std::floor(Global::METER_X_PADDING * 0.5));

    widget_label_.setBounds(0, 0, label_section_width, db_scale_height);

    db_scale_top_.setBounds(meter_section_x, 0, meter_section_width, db_scale_height);
    db_scale_bottom_.setBounds(meter_section_x, bounds.getBottom() - db_scale_height, meter_section_width, db_scale_height);

    meter_labels_.setBounds(label_group_x, db_scale_height, label_section_width, label_group_height);
    meters_.setBounds(meter_section_x + Global::METER_X_PADDING, db_scale_height, meter_group_width, meter_group_height);

    // Reset button.
    const juce::Rectangle< int > reset_bounds(bounds.getRight() - reset_button_width,
                                              0,
                                              reset_button_width,
                                              db_scale_height);

    const int reset_padding = 6;

    reset_button_.setBounds(reset_bounds.withSizeKeepingCentre(reset_bounds.getWidth() - (reset_padding * 2),
                                                               reset_bounds.getHeight() - (reset_padding * 2)));
}

/*---------------------------------------------------------------------------
**
*/
CustomTextButton&
LufsMetersWidget::getResetButton()
{
    return reset_button_;
}

/*---------------------------------------------------------------------------
** End of File
*/
