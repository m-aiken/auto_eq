#include "Theme.h"
#include "WarningLabel.h"

/*---------------------------------------------------------------------------
**
*/
WarningLabel::WarningLabel(const juce::String&       component_name,
                           const juce::String&       label_text,
                           const juce::Justification justification)
    : DisableableLabel(component_name, label_text, justification)
{
    text_colour_ = Theme::WARNING_TEXT;
    font_        = Theme::getFont().italicised();
}

/*---------------------------------------------------------------------------
** End of File
*/
