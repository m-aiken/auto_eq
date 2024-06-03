#include "MonoMeter.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
MonoMeter::MonoMeter(std::function< float() >&& callback_fn)
    : getValue(std::move(callback_fn))
{
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
    auto bounds = getLocalBounds();

    auto y = juce::jmap< float >(getValue(), Global::NEG_INF, Global::MAX_DB, bounds.getBottom(), 0);

    juce::Rectangle< float > meter_rect(bounds.getX(), y, bounds.getWidth(), bounds.getHeight() - y);

    g.setColour(juce::Colours::green);
    g.fillRect(meter_rect);
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
