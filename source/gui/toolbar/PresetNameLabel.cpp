#include "Theme.h"
#include "PresetManager.h"
#include "PresetNameLabel.h"

/*---------------------------------------------------------------------------
**
*/
PresetNameLabel::PresetNameLabel(const juce::String&       component_name,
                                 const juce::String&       label_text,
                                 const juce::Justification justification)
    : DisableableLabel(component_name, label_text, justification)
{
}

/*---------------------------------------------------------------------------
**
*/
void
PresetNameLabel::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
#endif

    const bool is_default_name = (getText() == PresetManager::DEFAULT_PRESET_NAME);
    text_colour_               = (is_default_name ? Theme::DEFAULT_PRESET_NAME_TEXT : Theme::TEXT);
    font_                      = (is_default_name ? Theme::getFont().italicised() : Theme::getFont());

    DisableableLabel::paint(g);
}

/*---------------------------------------------------------------------------
** End of File
*/
