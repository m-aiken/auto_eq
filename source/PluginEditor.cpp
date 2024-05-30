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
    , analyser_(p)
{
    addAndMakeVisible(theme_button_);
    addAndMakeVisible(analyser_);

    theme_button_.setToggleState(Theme::dark_mode, juce::dontSendNotification);
    theme_button_.onClick = [this]() {
        Theme::toggleTheme();
        repaint();
    };

    setSize(800, 600);
}

/*---------------------------------------------------------------------------
**
*/
PluginEditor::~PluginEditor()
{
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Theme::getColour(Theme::MAIN_BG));

    g.setColour(Theme::getColour(Theme::TEXT));
    g.setFont(15.0f);
    g.drawFittedText("ReLufs", getLocalBounds(), juce::Justification::centredTop, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::resized()
{
    auto        bounds             = getLocalBounds();
    const uint8 theme_button_width = 20;

    theme_button_.setBounds(bounds.getRight() - (theme_button_width * 2),
                            theme_button_width,
                            theme_button_width,
                            theme_button_width);

    analyser_.setBounds(bounds.reduced(30));
}

/*---------------------------------------------------------------------------
** End of File
*/
