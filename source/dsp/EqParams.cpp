#include "EqParams.h"

/*static*/ const int   EqParams::VERSION_HINT = 1;
/*static*/ const float EqParams::DEFAULT_Q    = 1.f;

/*---------------------------------------------------------------------------
**
*/
EqParams::EqParams()
{
}

/*---------------------------------------------------------------------------
**
*/
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
/*static*/ void
EqParams::addFreqParamToLayout(ParamLayout& pl, PARAM_ID id, float min_hz, float max_hz)
{
    ValueRange range(min_hz, max_hz, 1.f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id),
                                                         getName(id),
                                                         range,
                                                         getDefaultFrequency(id)));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addGainParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(Global::NEG_INF, Global::MAX_DB, 0.5f, 1.f);
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(id), getName(id), range, 0.f));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
EqParams::addQualParamToLayout(ParamLayout& pl, PARAM_ID id)
{
    ValueRange range(DEFAULT_Q, DEFAULT_Q, 0.05f, DEFAULT_Q);
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
