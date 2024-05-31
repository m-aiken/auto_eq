#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/Theme.h"

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , theme_button_()
    , primary_analyser_(p)
    , sidechain_analyser_(p)
{
    addAndMakeVisible(theme_button_);
    addAndMakeVisible(primary_analyser_);
    addAndMakeVisible(sidechain_analyser_);

    theme_button_.addListener(this);

    setSize(800, 600);
}

/*---------------------------------------------------------------------------
**
*/
PluginEditor::~PluginEditor()
{
    theme_button_.removeListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Theme::getColour(Theme::MAIN_BG));
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::resized()
{
    auto        bounds              = getLocalBounds();
    const uint8 theme_button_width  = 64;
    const uint8 theme_button_height = 32;
    const uint8 theme_button_margin = 10;

    theme_button_.setBounds(bounds.getRight() - theme_button_width - theme_button_margin,
                            theme_button_margin,
                            theme_button_width,
                            theme_button_height);

    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    grid.autoColumns  = Track(Fr(1));
    grid.templateRows = {
        Track(Fr(1)),
        Track(Fr(1)),
    };

    grid.items.add(juce::GridItem(primary_analyser_));
    grid.items.add(juce::GridItem(sidechain_analyser_));

    //    grid.setGap(juce::Grid::Px { 4 });
    grid.performLayout(bounds.reduced(30));
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

    if (button == &theme_button_) {
        repaint();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
