#include "DisableableLabel.h"
#include "GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
DisableableLabel::DisableableLabel(const juce::String&       component_name,
                                   const juce::String&       label_text,
                                   const juce::Justification justification)
    : juce::Label(component_name, label_text)
    , text_colour_(Theme::TEXT)
    , font_(Theme::getFont())
{
    setJustificationType(justification);
}

/*---------------------------------------------------------------------------
**
*/
void
DisableableLabel::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
#endif

    g.setColour(Theme::getColour(isEnabled() ? text_colour_ : Theme::DISABLED_WIDGET));
    g.setFont(font_);
    g.drawFittedText(getText(), getLocalBounds(), getJustificationType(), 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
