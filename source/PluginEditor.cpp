#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/Theme.h"
#include "utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , menu_()
    , filter_res_graph_(p)
    , meter_group_(p)
{
    addAndMakeVisible(menu_);
    addAndMakeVisible(filter_res_graph_);
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
    auto        bounds      = getLocalBounds();
    const uint8 menu_height = 32;

    menu_.setBounds(0, 0, bounds.getWidth(), menu_height);
    filter_res_graph_.setBounds(0, menu_.getBottom(), bounds.getWidth(), bounds.getHeight() * 0.5);

#if 0
    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    grid.templateColumns = {
        Track(Fr(75)),
        Track(Fr(25)),
    };

    grid.templateRows = {
        Track(Fr(40)),
        Track(Fr(60)),
    };

    grid.items.add(juce::GridItem(filter_res_graph_));
    grid.items.add(juce::GridItem());
    grid.items.add(juce::GridItem(analyser_));
    grid.items.add(juce::GridItem(meter_group_));

    grid.performLayout(bounds.reduced(30));
#endif
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
