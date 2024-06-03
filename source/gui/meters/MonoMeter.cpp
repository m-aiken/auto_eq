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
    auto  bounds = getLocalBounds();
    float val    = getValue();

    auto y = juce::jmap< float >(val, Global::NEG_INF, Global::MAX_DB, bounds.getBottom(), 0);

    juce::Rectangle< float > meter_rect(bounds.getX(), y, bounds.getWidth(), bounds.getHeight() - y);

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
