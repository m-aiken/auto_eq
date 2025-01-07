#include "DisableableLabel.h"
#include "GlobalConstants.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
DisableableLabel::DisableableLabel(const juce::String&       component_name,
                                   const juce::String&       label_text,
                                   const juce::Justification justification,
                                   const bool                is_warning)
    : juce::Label(component_name, label_text)
    , is_warning_label_(is_warning)
    , font_(is_warning ? Theme::getFont().italicised() : Theme::getFont())
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

    const juce::Colour enabled_colour = Theme::getColour(is_warning_label_ ? Theme::WARNING_TEXT : Theme::TEXT);

    g.setColour(isEnabled() ? enabled_colour : Theme::getColour(Theme::DISABLED_WIDGET));
    g.setFont(font_);
    g.drawFittedText(getText(), getLocalBounds(), getJustificationType(), 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
