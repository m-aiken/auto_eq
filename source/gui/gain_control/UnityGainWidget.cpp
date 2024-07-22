#include "UnityGainWidget.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
UnityGainWidget::UnityGainWidget(juce::AudioProcessorValueTreeState& apvts)
    : enable_button_("Unity Gain", apvts, GuiParams::UNITY_GAIN)
    , gain_selector_label_()
    , gain_selector_(juce::Range< double >(-12.0, 0.0), -3.0, "dB")
{
    addAndMakeVisible(enable_button_);
    addAndMakeVisible(gain_selector_label_);
    addAndMakeVisible(gain_selector_);

    gain_selector_label_.setText("Target dB:", juce::dontSendNotification);
    gain_selector_label_.setFont(Theme::getFont());
    gain_selector_label_.setColour(juce::Label::ColourIds::textColourId, Theme::getColour(Theme::TEXT));
}

/*---------------------------------------------------------------------------
**
*/
void
UnityGainWidget::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::green);
    g.drawRect(getLocalBounds());
#endif

    g.setColour(Theme::getColour(Theme::SECTION_BORDER));
    g.drawRect(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
UnityGainWidget::resized()
{
    auto og_bounds        = getLocalBounds();
    auto og_bounds_width  = og_bounds.getWidth();
    auto og_bounds_height = og_bounds.getHeight();
    auto button_margin    = og_bounds_height * 0.1;

    enable_button_.setBounds(button_margin, button_margin, og_bounds_width - (button_margin * 2), og_bounds_height * 0.2);

    auto padded_bounds = og_bounds.withSizeKeepingCentre(og_bounds_width * 0.4, og_bounds_height * 0.3);

    using Tr = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Tr(Fr(1));

    grid.templateRows = {
        Tr(Fr(40)),
        Tr(Fr(60)),
    };

    grid.items.add(juce::GridItem(gain_selector_label_));
    grid.items.add(juce::GridItem(gain_selector_));

    grid.performLayout(padded_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
