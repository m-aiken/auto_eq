#include "ButtonWithLabel.h"

/*---------------------------------------------------------------------------
**
*/
ButtonWithLabel::ButtonWithLabel(juce::AudioProcessorValueTreeState& apvts,
                                 GuiParams::PARAM_ID                 param_id,
                                 const juce::String&                 label_text)
    : button_(apvts, param_id)
    , label_("button_label_" + label_text.replaceCharacters(" ", "_"), label_text, juce::Justification::centredLeft)
{
    addAndMakeVisible(button_);
    addAndMakeVisible(label_);
}

/*---------------------------------------------------------------------------
**
*/
void
ButtonWithLabel::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds());
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
ButtonWithLabel::resized()
{
    juce::Rectangle< int > bounds          = getLocalBounds();
    int                    bounds_width    = bounds.getWidth();
    int                    bounds_height   = bounds.getHeight();
    int                    button_diameter = juce::jmin(bounds_width, bounds_height);
    const int              padding         = 8;

    button_.setBounds(0, 0, button_diameter, button_diameter);
    label_.setBounds(button_.getRight() + padding, 0, bounds_width - button_diameter - padding, bounds_height);
}

/*---------------------------------------------------------------------------
**
*/
SquareToggleButton&
ButtonWithLabel::getButton()
{
    return button_;
}

/*---------------------------------------------------------------------------
** End of File
*/
