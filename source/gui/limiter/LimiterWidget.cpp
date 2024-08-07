#include "GlobalConstants.h"
#include "LimiterWidget.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
LimiterWidget::LimiterWidget(juce::AudioProcessorValueTreeState& apvts)
    : enable_button_("Limiter", apvts, GuiParams::LIMITER_ENABLED)
    , threshold_label_("limiter_threshold_label", "Threshold")
    , threshold_control_(apvts, GuiParams::getName(GuiParams::LIMITER_THRESHOLD))
{
    addAndMakeVisible(enable_button_);
    addAndMakeVisible(threshold_label_);
    addAndMakeVisible(threshold_control_);

    enable_button_.addListener(this);

    threshold_label_.setEnabled(GuiParams::INITIAL_LIMITER_STATE);
    threshold_control_.setEnabled(GuiParams::INITIAL_LIMITER_STATE);
}

/*---------------------------------------------------------------------------
**
*/
LimiterWidget::~LimiterWidget()
{
    enable_button_.removeListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
LimiterWidget::paint(juce::Graphics& g)
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
LimiterWidget::resized()
{
    auto og_bounds        = getLocalBounds();
    auto og_bounds_width  = og_bounds.getWidth();
    auto og_bounds_height = og_bounds.getHeight();
    auto button_margin    = og_bounds_height * 0.1;

    enable_button_.setBounds(button_margin, button_margin, og_bounds_width - (button_margin * 2), og_bounds_height * 0.2);

    auto padded_bounds = og_bounds.withSizeKeepingCentre(og_bounds_width * 0.4, og_bounds_height * 0.6);

    using Tr = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Tr(Fr(1));

    grid.templateRows = {
        Tr(Fr(80)),
        Tr(Fr(20)),
    };

    grid.items.add(juce::GridItem(threshold_control_));
    grid.items.add(juce::GridItem(threshold_label_));

    grid.performLayout(padded_bounds);
}

/*---------------------------------------------------------------------------
**
*/
void
LimiterWidget::buttonClicked(juce::Button* button)
{
    if (button == nullptr) {
        return;
    }

    if (button == &enable_button_) {
        bool component_enabled = enable_button_.getToggleState();

        threshold_label_.setEnabled(component_enabled);
        threshold_control_.setEnabled(component_enabled);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
