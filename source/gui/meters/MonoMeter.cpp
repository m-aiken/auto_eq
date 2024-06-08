#include "MonoMeter.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
MonoMeter::MonoMeter(std::function< float() >&& callback_fn)
    : getValue(std::move(callback_fn))
{
    addAndMakeVisible(backdrop_);

    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
MonoMeter::~MonoMeter()
{
    stopTimer();
}

/*---------------------------------------------------------------------------
**
*/
void
MonoMeter::paint(juce::Graphics& g)
{
    auto  bounds        = getLocalBounds();
    auto  bounds_width  = bounds.getWidth();
    auto  bounds_height = bounds.getHeight();
    float val           = getValue();
    auto  length        = juce::jmap< float >(val, Global::NEG_INF, Global::MAX_DB, 0, bounds_width);

    juce::Rectangle< float > meter_rect(0, 0, length, bounds_height);

    //    g.setColour(Theme::getColour(val >= -6.f ? Theme::METER_HOT : Theme::METER_COLD));
    g.setColour(Theme::getColour(Theme::METER_COLD));
    g.fillRect(meter_rect);
}

/*---------------------------------------------------------------------------
**
*/
void
MonoMeter::resized()
{
    backdrop_.setBounds(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
void
MonoMeter::timerCallback()
{
    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
