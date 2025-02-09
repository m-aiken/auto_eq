#include "ReadonlyTextBox.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
ReadonlyTextBox::ReadonlyTextBox(const juce::String& initial_text)
    : label_("readonly_textbox", initial_text)
{
    addAndMakeVisible(label_);
}

/*---------------------------------------------------------------------------
**
*/
void
ReadonlyTextBox::paint(juce::Graphics& g)
{
    g.fillAll(Theme::getColour(Theme::READONLY_TEXTBOX_BG));
}

/*---------------------------------------------------------------------------
**
*/
void
ReadonlyTextBox::resized()
{
    label_.setBounds(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
ReadonlyTextBox::setText(const juce::String& text)
{
    label_.setText(text, juce::dontSendNotification);
    label_.repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
