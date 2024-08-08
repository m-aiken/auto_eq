#include "GlobalConstants.h"
#include "SpinBox.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
SpinBox::SpinBox(juce::RangedAudioParameter* param, float interval)
    : interval_(interval)
    , value_box_(param)
    , up_button_(true)
    , down_button_(false)
    , param_(param)
{
    addAndMakeVisible(value_box_);
    addAndMakeVisible(up_button_);
    addAndMakeVisible(down_button_);

    up_button_.addListener(this);
    down_button_.addListener(this);
}

/*---------------------------------------------------------------------------
**
*/
SpinBox::~SpinBox()
{
    up_button_.removeListener(this);
    down_button_.removeListener(this);
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
    grid.templateColumns = { Tr(Fr(50)), Tr(Fr(25)), Tr(Fr(25)) };

    grid.items.add(juce::GridItem(value_box_));
    grid.items.add(juce::GridItem(up_button_));
    grid.items.add(juce::GridItem(down_button_));

    grid.setGap(Px(4));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
SpinBox::buttonClicked(juce::Button* button)
{
    if (button == nullptr || param_ == nullptr) {
        return;
    }

    float value = param_->convertFrom0to1(param_->getValue());

    if (button == &up_button_) {
        value += interval_;
    }
    else if (button == &down_button_) {
        value -= interval_;
    }

    param_->beginChangeGesture();
    param_->setValueNotifyingHost(param_->convertTo0to1(value));
    param_->endChangeGesture();

    value_box_.repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
