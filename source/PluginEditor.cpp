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
    , theme_button_()
    , analyser_(p)
    , meter_group_(p)
{
    addAndMakeVisible(theme_button_);
    addAndMakeVisible(analyser_);
    addAndMakeVisible(meter_group_);

    theme_button_.addListener(this);

    setSize(1000, 500);
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

    grid.autoRows        = Track(Fr(1));
    grid.templateColumns = {
        Track(Fr(75)),
        Track(Fr(25)),
    };

    grid.items.add(juce::GridItem(analyser_));
    grid.items.add(juce::GridItem(meter_group_));

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
