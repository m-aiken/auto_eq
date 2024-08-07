#include "GlobalConstants.h"
#include "SpinBoxTextBox.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
SpinBoxTextBox::SpinBoxTextBox(juce::RangedAudioParameter* param)
    : juce::Label()
    , param_(param)
{
    setFont(Theme::getFont());
    setText("0.0", juce::dontSendNotification);
}

/*---------------------------------------------------------------------------
**
*/
void
SpinBoxTextBox::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::yellow);
    g.drawRect(getLocalBounds());
#endif

    if (param_ == nullptr) {
        return;
    }

    float        value = param_->convertFrom0to1(param_->getValue());
    juce::String value_str(value, 1);

    // Background.
    g.fillAll(Theme::getColour(isEnabled() ? Theme::UNITY_GAIN_VALUE_BOX : Theme::DISABLED_WIDGET));

    // Value.
    g.setColour(Theme::getColour(isEnabled() ? Theme::TEXT : Theme::DISABLED_WIDGET));
    g.setFont(Theme::getFont());
    g.drawFittedText(value_str, getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
