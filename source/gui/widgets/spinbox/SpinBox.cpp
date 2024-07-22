#include "SpinBox.h"
#include "../../look_and_feel/Theme.h"
#include "../../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
SpinBox::SpinBox(juce::Range< double > range, double default_value, const juce::String& unit)
    : up_button_(true)
    , down_button_(false)
{
    unit_label_.setText(unit, juce::dontSendNotification);
    unit_label_.setFont(Theme::getFont());
    unit_label_.setColour(juce::Label::ColourIds::textColourId, Theme::getColour(Theme::TEXT));

    addAndMakeVisible(value_box_);
    addAndMakeVisible(unit_label_);
    addAndMakeVisible(up_button_);
    addAndMakeVisible(down_button_);

    //    setRange(range, 0.1);
    //    setValue(default_value, juce::dontSendNotification);
}

/*---------------------------------------------------------------------------
**
*/
void
SpinBox::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
SpinBox::resized()
{
    using Tr = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using Px = juce::Grid::Px;

    juce::Grid grid;

    grid.autoRows        = Tr(Fr(1));
    grid.templateColumns = { Tr(Fr(40)), Tr(Fr(10)), Tr(Fr(25)), Tr(Fr(25)) };

    grid.items.add(juce::GridItem(value_box_));
    grid.items.add(juce::GridItem(unit_label_));
    grid.items.add(juce::GridItem(up_button_));
    grid.items.add(juce::GridItem(down_button_));

    grid.setGap(Px(4));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
