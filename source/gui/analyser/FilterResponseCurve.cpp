#include "FilterResponseCurve.h"

/*---------------------------------------------------------------------------
**
*/
FilterResponseCurve::FilterResponseCurve(PluginProcessor& p)
    : processor_ref_(p)
    , apvts_value_changed_(false)
{
    addApvtsListeners();
    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
FilterResponseCurve::~FilterResponseCurve()
{
    stopTimer();
    removeApvtsListeners();
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::parameterValueChanged(int parameter_index, float new_value)
{
    juce::ignoreUnused(parameter_index, new_value);

    apvts_value_changed_.set(true);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::parameterGestureChanged(int parameter_index, bool gesture_is_starting)
{
    // Do nothing - only implemented because it's pure virtual.
    juce::ignoreUnused(parameter_index, gesture_is_starting);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::timerCallback()
{
    if (apvts_value_changed_.compareAndSetBool(false, true)) {
        repaint();
    }
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::addApvtsListeners()
{
    juce::AudioProcessorValueTreeState& apvts = processor_ref_.getApvts();

    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_SLOPE))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_ENABLED))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_GAIN))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_Q))->addListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_FREQ))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_SLOPE))->addListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_ENABLED))->addListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseCurve::removeApvtsListeners()
{
    juce::AudioProcessorValueTreeState& apvts = processor_ref_.getApvts();

    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_SLOPE))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_CUT_ENABLED))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::LOW_SHELF_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_1_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_2_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_3_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_4_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::PEAK_5_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_GAIN))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_SHELF_Q))->removeListener(this);
    //
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_FREQ))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_SLOPE))->removeListener(this);
    apvts.getParameter(EqParams::getName(EqParams::HIGH_CUT_ENABLED))->removeListener(this);
}

/*---------------------------------------------------------------------------
** End of File
*/
