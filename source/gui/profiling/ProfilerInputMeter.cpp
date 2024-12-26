#include "GlobalConstants.h"
#include "ProfilerInputMeter.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
ProfilerInputMeter::ProfilerInputMeter(PluginProcessor& p)
    : processor_ref_(p)
{
    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
ProfilerInputMeter::~ProfilerInputMeter()
{
    stopTimer();
}

/*---------------------------------------------------------------------------
**
*/
void
ProfilerInputMeter::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::yellow);
    g.drawRect(getLocalBounds());
#endif

    const auto  bounds        = getLocalBounds();
    const auto  bounds_width  = bounds.getWidth();
    const auto  bounds_height = bounds.getHeight();
    const float val           = processor_ref_.getInputGainValue();
    const auto  length        = juce::jmap< float >(val, Global::METER_NEG_INF, Global::METER_MAX_DB, 0, bounds_height);

    const juce::Rectangle< float > meter_rect(0, bounds.getBottom() - length, bounds_width, length);

    g.setColour(Theme::getColour(Theme::METER_VALUE));
    g.fillRect(meter_rect);
}

/*---------------------------------------------------------------------------
**
*/
void
ProfilerInputMeter::timerCallback()
{
    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
