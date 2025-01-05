#include "GlobalConstants.h"
#include "MetersWidget.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MetersWidget::MetersWidget(PluginProcessor& p)
    : db_scale_top_(Global::Meters::HORIZONTAL)
    , db_scale_bottom_(Global::Meters::HORIZONTAL)
    , meters_(p)
{
    addAndMakeVisible(db_scale_top_);
    addAndMakeVisible(db_scale_bottom_);
    addAndMakeVisible(meter_labels_);
    addAndMakeVisible(meters_);
}

/*---------------------------------------------------------------------------
**
*/
void
MetersWidget::paint(juce::Graphics& g)
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
MetersWidget::resized()
{
    const juce::Rectangle< int > bounds              = getLocalBounds();
    const int                    bounds_width        = bounds.getWidth();
    const int                    bounds_height       = bounds.getHeight();
    const int                    label_section_width = static_cast< int >(std::floor(bounds_width * 0.2));
    const int                    meter_section_width = static_cast< int >(std::floor(bounds_width * 0.8));

    const int meter_section_x    = label_section_width;
    const int db_scale_height    = static_cast< int >(std::floor(bounds_height * 0.2));
    const int meter_group_height = static_cast< int >(std::floor(bounds_height * 0.6));
    const int meter_group_width  = static_cast< int >(std::floor(meter_section_width - (Global::METER_X_PADDING * 2)));
    const int label_group_height = meter_group_height;

    // Shift the labels left a bit to account for the padding around the meters.
    // They're too far away otherwise.
    const int label_group_x = static_cast< int >(std::floor(Global::METER_X_PADDING * 0.5));

    db_scale_top_.setBounds(meter_section_x, 0, meter_section_width, db_scale_height);
    db_scale_bottom_.setBounds(meter_section_x, bounds.getBottom() - db_scale_height, meter_section_width, db_scale_height);

    meter_labels_.setBounds(label_group_x, db_scale_height, label_section_width, label_group_height);
    meters_.setBounds(meter_section_x + Global::METER_X_PADDING, db_scale_height, meter_group_width, meter_group_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
