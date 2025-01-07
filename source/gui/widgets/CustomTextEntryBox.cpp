#include "CustomTextEntryBox.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
CustomTextEntryBox::CustomTextEntryBox(const juce::String& placeholder_text)
    : placeholder_text_(placeholder_text)
{
    setFont(Theme::getFont());
    setJustification(juce::Justification::centred);
    setInputRestrictions(MAX_CHARS);
    setMultiLine(false);
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextEntryBox::paint(juce::Graphics& g)
{
    const auto& bounds        = getLocalBounds();
    const int   bounds_width  = bounds.getWidth();
    const int   bounds_height = bounds.getHeight();

    getLookAndFeel().fillTextEditorBackground(g, bounds_width, bounds_height, *this);
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextEntryBox::mouseEnter(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    setMouseCursor(isEnabled() ? juce::MouseCursor::PointingHandCursor : juce::MouseCursor::NormalCursor);
}

/*---------------------------------------------------------------------------
**
*/
void
CustomTextEntryBox::resetTextColour()
{
    setColour(juce::TextEditor::ColourIds::textColourId, Theme::getColour(Theme::TEXT));
    setTextToShowWhenEmpty(placeholder_text_, Theme::getColour(Theme::TEXT));
}

/*---------------------------------------------------------------------------
** End of File
*/
