#include "UnityGainWidget.h"
#include "../look_and_feel/Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
UnityGainWidget::UnityGainWidget(juce::AudioProcessorValueTreeState& apvts)
    : enable_button_("Unity Gain", apvts, GuiParams::UNITY_GAIN_ENABLED)
    , gain_selector_label_("unity_gain_target_db_label", "Target dB:")
    , gain_selector_(apvts.getParameter(GuiParams::getName(GuiParams::UNITY_GAIN_VALUE)))
{
    addAndMakeVisible(enable_button_);
    addAndMakeVisible(gain_selector_label_);
    addAndMakeVisible(gain_selector_);

    enable_button_.addListener(this);

    gain_selector_label_.setEnabled(GuiParams::INITIAL_UNITY_GAIN_STATE);
    gain_selector_.setEnabled(GuiParams::INITIAL_UNITY_GAIN_STATE);
}

/*---------------------------------------------------------------------------
**
*/
UnityGainWidget::~UnityGainWidget()
{
    enable_button_.removeListener(this);
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
**
*/
void
UnityGainWidget::buttonClicked(juce::Button* button)
{
    if (button == nullptr) {
        return;
    }

    if (button == &enable_button_) {
        bool component_enabled = enable_button_.getToggleState();

        gain_selector_label_.setEnabled(component_enabled);
        gain_selector_.setEnabled(component_enabled);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
