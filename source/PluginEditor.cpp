#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/Theme.h"

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , menu_()
    , filter_res_graph_(p)
    , intensity_control_(p.getApvts())
    , meter_group_(p)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(menu_);
    addAndMakeVisible(filter_res_graph_);
    addAndMakeVisible(intensity_control_);
    addAndMakeVisible(meter_group_);

    menu_.getThemeButtonRef().addListener(this);

    setResizable(true, true);
    setResizeLimits(768, 400, 1100, 600);
    setSize(1000, 500);
}

/*---------------------------------------------------------------------------
**
*/
PluginEditor::~PluginEditor()
{
    menu_.getThemeButtonRef().removeListener(this);
    setLookAndFeel(nullptr);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(Theme::getColour(Theme::MAIN_BG));
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.templateColumns = {
        Track(Fr(1)),
    };

    grid.templateRows = {
        Track(Fr(5)),
        Track(Fr(55)),
        Track(Fr(15)),
        Track(Fr(25)),
    };

    grid.items.add(juce::GridItem(menu_));
    grid.items.add(juce::GridItem(filter_res_graph_));
    grid.items.add(juce::GridItem(intensity_control_));
    grid.items.add(juce::GridItem(meter_group_));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::buttonClicked(juce::Button* button)
{
    if (button == nullptr) {
        return;
    }

    if (button == &menu_.getThemeButtonRef()) {
        repaint();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
