#include "PluginProcessor.h"
#include "PluginEditor.h"

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , analyser_(p)
{
    addAndMakeVisible(analyser_);

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
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("ReLufs", getLocalBounds(), juce::Justification::centredTop, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::resized()
{
    auto bounds = getLocalBounds();

    analyser_.setBounds(bounds.reduced(30));
}

/*---------------------------------------------------------------------------
** End of File
*/
