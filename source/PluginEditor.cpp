#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/look_and_feel/Theme.h"

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , fft_menu_(p.getApvts())
    , menu_()
    , filter_res_graph_(p)
    , intensity_control_(p.getApvts())
    , meter_group_(p)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(fft_menu_);
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
    auto bounds          = getLocalBounds();
    auto bounds_height   = bounds.getHeight();
    auto bounds_width    = bounds.getWidth();
    auto menu_height     = bounds_height * 0.05;
    auto graph_height    = bounds_height * 0.65;
    auto meters_height   = bounds_height * 0.3;
    auto meters_width    = bounds_width * 0.75;
    auto intensity_width = bounds_width * 0.25;

    fft_menu_.setBounds(0, 0, bounds_width * 0.7, menu_height);
    //    menu_.setBounds(0, 0, bounds_width, menu_height);
    filter_res_graph_.setBounds(0, menu_height, bounds_width, graph_height);
    intensity_control_.setBounds(0, filter_res_graph_.getBottom(), intensity_width, meters_height);
    meter_group_.setBounds(intensity_control_.getRight(), filter_res_graph_.getBottom(), meters_width, meters_height);

#if 0
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
