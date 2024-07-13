#include "InputAnalysisMenu.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
InputAnalysisMenu::InputAnalysisMenu(PluginProcessor& processor_ref)
    : analyse_input_button_("Analyse Input", processor_ref.getApvts(), GuiParams::ANALYSE_INPUT)
    , processor_ref_(processor_ref)
{
    addAndMakeVisible(analyse_input_button_);

    analyse_input_button_.addListener(this);
}

/*---------------------------------------------------------------------------
**
*/
InputAnalysisMenu::~InputAnalysisMenu()
{
    analyse_input_button_.removeListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisMenu::paint(juce::Graphics& g)
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
InputAnalysisMenu::resized()
{
    juce::Rectangle< int > bounds  = getLocalBounds();
    const uint8            padding = 6;
    juce::Rectangle< int > bounds_reduced(padding,
                                          padding,
                                          bounds.getWidth() - (padding * 2),
                                          bounds.getHeight() - (padding * 2));

    using Tr = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoRows        = Tr(Fr(1));
    grid.templateColumns = { Tr(Fr(1)) };

    grid.items.add(juce::GridItem(analyse_input_button_));

    grid.performLayout(bounds_reduced);
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisMenu::buttonClicked(juce::Button* button)
{
    if (button != nullptr && button == &analyse_input_button_) {
        analyse_input_button_.getToggleState() ? processor_ref_.startInputAnalysis() : processor_ref_.stopInputAnalysis();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
