#include "EqParams.h"
#include "../utility/GlobalConstants.h"

/*static*/ const float EqParams::MIN_Q     = 0.1f;
/*static*/ const float EqParams::MAX_Q     = 10.f;
/*static*/ const float EqParams::DEFAULT_Q = 1.f;

/*---------------------------------------------------------------------------
**
*/
EqParams::EqParams()
{
}

/*static*/ const juce::String
EqParams::getParamName(PARAM_ID param_id)
{
    switch (param_id) {
    case LOW_CUT_FREQ:
        return "Low Cut Freq";

    case LOW_CUT_SLOPE:
        return "Low Cut Slope";

    case LOW_CUT_ENABLED:
        return "Low Cut Enabled";

    case PEAK_1_FREQ:
        return "Peak 1 Freq";

    case PEAK_1_GAIN:
        return "Peak 1 Gain";

    case PEAK_1_Q:
        return "Peak 1 Q";

    case PEAK_2_FREQ:
        return "Peak 2 Freq";

    case PEAK_2_GAIN:
        return "Peak 2 Gain";

    case PEAK_2_Q:
        return "Peak 2 Q";

    case PEAK_3_FREQ:
        return "Peak 3 Freq";

    case PEAK_3_GAIN:
        return "Peak 3 Gain";

    case PEAK_3_Q:
        return "Peak 3 Q";

    case PEAK_4_FREQ:
        return "Peak 4 Freq";

    case PEAK_4_GAIN:
        return "Peak 4 Gain";

    case PEAK_4_Q:
        return "Peak 4 Q";

    case PEAK_5_FREQ:
        return "Peak 5 Freq";

    case PEAK_5_GAIN:
        return "Peak 5 Gain";

    case PEAK_5_Q:
        return "Peak 5 Q";

    case PEAK_6_FREQ:
        return "Peak 6 Freq";

    case PEAK_6_GAIN:
        return "Peak 6 Gain";

    case PEAK_6_Q:
        return "Peak 6 Q";

    case HIGH_CUT_FREQ:
        return "High Cut Freq";

    case HIGH_CUT_SLOPE:
        return "High Cut Slope";

    case HIGH_CUT_ENABLED:
        return "High Cut Enabled";

    default:
        return "";
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::StringArray
EqParams::getSlopeChoices()
{
    return juce::StringArray("12dB/Oct", "24dB/Oct", "36dB/Oct", "48dB/Oct");
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
EqParams::getDefaultPeakFrequency(PARAM_ID param_id)
{
    if (param_id == PEAK_1_FREQ) {
        return 100.f;
    }
    else if (param_id == PEAK_2_FREQ) {
        return 200.f;
    }
    else if (param_id == PEAK_3_FREQ) {
        return 500.f;
    }
    else if (param_id == PEAK_4_FREQ) {
        return 1000.f;
    }
    else if (param_id == PEAK_5_FREQ) {
        return 2000.f;
    }
    else if (param_id == PEAK_6_FREQ) {
        return 5000.f;
    }

    return Global::NEG_INF;
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addPeakFreqParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(Global::MIN_HZ, Global::MAX_HZ, 1.f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(id, getParamName(id), range, getDefaultPeakFrequency(id)));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addPeakGainParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(Global::NEG_INF, Global::MAX_DB, 0.5f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(id, getParamName(id), range, 0.f));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addPeakQualParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(MIN_Q, MAX_Q, 0.05f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(id, getParamName(id), range, DEFAULT_Q));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addEnabledParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    pl.add(std::make_unique< juce::AudioParameterBool >(id, getParamName(id), false));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addCutFreqParamToLayout(ParamLayout& pl, PARAM_ID id, const float default_value)
{
    ValueRange range(Global::MIN_HZ, Global::MAX_HZ, 1.f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(id, getParamName(id), range, default_value));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addCutChoiceParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    pl.add(std::make_unique< juce::AudioParameterChoice >(id, getParamName(id), getSlopeChoices(), DB_PER_OCT_12));
}

/*---------------------------------------------------------------------------
** End of File
*/
