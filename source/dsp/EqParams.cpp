#include "EqParams.h"
#include "../utility/GlobalConstants.h"

/*static*/ const int EqParams::VERSION_HINT = 1;

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
EqParams::getName(PARAM_ID param_id)
{
    switch (param_id) {
    case LOW_CUT_FREQ:
        return "lc_freq";

    case LOW_CUT_SLOPE:
        return "lc_slope";

    case LOW_CUT_ENABLED:
        return "lc_enabled";

    case LOW_SHELF_FREQ:
        return "ls_freq";

    case LOW_SHELF_GAIN:
        return "ls_gain";

    case LOW_SHELF_Q:
        return "ls_q";

    case PEAK_1_FREQ:
        return "p1_freq";

    case PEAK_1_GAIN:
        return "p1_gain";

    case PEAK_1_Q:
        return "p1_q";

    case PEAK_2_FREQ:
        return "p2_freq";

    case PEAK_2_GAIN:
        return "p2_gain";

    case PEAK_2_Q:
        return "p2_q";

    case PEAK_3_FREQ:
        return "p3_freq";

    case PEAK_3_GAIN:
        return "p3_gain";

    case PEAK_3_Q:
        return "p3_q";

    case PEAK_4_FREQ:
        return "p4_freq";

    case PEAK_4_GAIN:
        return "p4_gain";

    case PEAK_4_Q:
        return "p4_q";

    case PEAK_5_FREQ:
        return "p5_freq";

    case PEAK_5_GAIN:
        return "p5_gain";

    case PEAK_5_Q:
        return "p5_q";

    case HIGH_SHELF_FREQ:
        return "hs_freq";

    case HIGH_SHELF_GAIN:
        return "hs_gain";

    case HIGH_SHELF_Q:
        return "hs_q";

    case HIGH_CUT_FREQ:
        return "hc_freq";

    case HIGH_CUT_SLOPE:
        return "hc_slope";

    case HIGH_CUT_ENABLED:
        return "hc_enabled";

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
        return 500.f;
    }
    else if (param_id == PEAK_3_FREQ) {
        return 1000.f;
    }
    else if (param_id == PEAK_4_FREQ) {
        return 2000.f;
    }
    else if (param_id == PEAK_5_FREQ) {
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
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id),
                                                         getName(id),
                                                         range,
                                                         getDefaultPeakFrequency(id)));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addPeakGainParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(Global::NEG_INF, Global::MAX_DB, 0.5f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id), getName(id), range, 0.f));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addPeakQualParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(MIN_Q, MAX_Q, 0.05f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id), getName(id), range, DEFAULT_Q));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addEnabledParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    pl.add(std::make_unique< juce::AudioParameterBool >(getVersionedParameterId(id), getName(id), false));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addCutFreqParamToLayout(ParamLayout& pl, PARAM_ID id, const float default_value)
{
    ValueRange range(Global::MIN_HZ, Global::MAX_HZ, 1.f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id), getName(id), range, default_value));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addCutChoiceParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    pl.add(std::make_unique< juce::AudioParameterChoice >(getVersionedParameterId(id),
                                                          getName(id),
                                                          getSlopeChoices(),
                                                          DB_PER_OCT_12));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addShelfFreqParamToLayout(ParamLayout& pl, PARAM_ID id, const float default_value)
{
    ValueRange range(Global::MIN_HZ, Global::MAX_HZ, 1.f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id), getName(id), range, default_value));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addShelfGainParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(Global::NEG_INF, Global::MAX_DB, 0.5f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id), getName(id), range, 0.f));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addShelfQualParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(MIN_Q, MAX_Q, 0.05f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id), getName(id), range, DEFAULT_Q));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::ParameterID
EqParams::getVersionedParameterId(PARAM_ID id)
{
    return juce::ParameterID(getName(id), VERSION_HINT);
}

/*---------------------------------------------------------------------------
** End of File
*/
