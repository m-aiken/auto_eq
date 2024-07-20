#include "SpinBox.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
SpinBox::SpinBox(juce::Range< double > range, double default_value, const juce::String& unit)
    : juce::Slider(juce::Slider::IncDecButtons, juce::Slider::TextBoxLeft)
{
    setRange(range, 0.1);
    setValue(default_value, juce::dontSendNotification);
}

/*---------------------------------------------------------------------------
**
*/
void
SpinBox::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds());
#endif
}

/*---------------------------------------------------------------------------
** End of File
*/
