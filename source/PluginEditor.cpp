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
    , peak_meter_(Global::PEAK_METER, p)
    , rms_meter_(Global::RMS_METER, p)
    , lufs_meter_(Global::LUFS_METER, p)
{
    addAndMakeVisible(theme_button_);
    addAndMakeVisible(analyser_);
    addAndMakeVisible(peak_meter_);
    addAndMakeVisible(rms_meter_);
    addAndMakeVisible(lufs_meter_);

    theme_button_.addListener(this);

    setSize(1000, 600);
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
    using Px    = juce::Grid::Px;

    grid.autoRows        = Track(Fr(1));
    grid.templateColumns = {
        Track(Fr(7)),
        Track(Fr(1)),
        Track(Fr(1)),
        Track(Fr(1)),
    };

    grid.items.add(juce::GridItem(analyser_));
    grid.items.add(juce::GridItem(peak_meter_));
    grid.items.add(juce::GridItem(rms_meter_));
    grid.items.add(juce::GridItem(lufs_meter_));

    grid.setGap(Px { 4 });

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
