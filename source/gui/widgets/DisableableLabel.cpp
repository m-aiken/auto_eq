#include "DisableableLabel.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
DisableableLabel::DisableableLabel(const juce::String& component_name,
                                   const juce::String& label_text,
                                   juce::Justification justification)
    : juce::Label(component_name, label_text)
{
    setJustificationType(justification);
}

/*---------------------------------------------------------------------------
**
*/
void
DisableableLabel::paint(juce::Graphics& g)
{
    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));
    g.drawFittedText(getText(), getLocalBounds(), getJustificationType(), 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
