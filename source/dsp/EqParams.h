#pragma once

#include <JuceHeader.h>

class EqParams
{
public:
    EqParams();

    static const int VERSION_HINT;

    static const float MIN_Q;
    static const float MAX_Q;
    static const float DEFAULT_Q;

    enum PARAM_ID {
        LOW_CUT_FREQ,
        LOW_CUT_SLOPE,
        LOW_CUT_ENABLED,
        //
        LOW_SHELF_FREQ,
        LOW_SHELF_GAIN,
        LOW_SHELF_Q,
        //
        PEAK_1_FREQ,
        PEAK_1_GAIN,
        PEAK_1_Q,
        //
        PEAK_2_FREQ,
        PEAK_2_GAIN,
        PEAK_2_Q,
        //
        PEAK_3_FREQ,
        PEAK_3_GAIN,
        PEAK_3_Q,
        //
        PEAK_4_FREQ,
        PEAK_4_GAIN,
        PEAK_4_Q,
        //
        PEAK_5_FREQ,
        PEAK_5_GAIN,
        PEAK_5_Q,
        //
        HIGH_SHELF_FREQ,
        HIGH_SHELF_GAIN,
        HIGH_SHELF_Q,
        //
        HIGH_CUT_FREQ,
        HIGH_CUT_SLOPE,
        HIGH_CUT_ENABLED,
    };

    enum SLOPE_CHOICE {
        DB_PER_OCT_12,
        DB_PER_OCT_24,
        DB_PER_OCT_36,
        DB_PER_OCT_48,
    };

    static const juce::String getName(PARAM_ID param_id);
    static juce::StringArray  getSlopeChoices();
    static float              getDefaultPeakFrequency(PARAM_ID param_id);

    typedef juce::AudioProcessorValueTreeState::ParameterLayout ParamLayout;
    typedef juce::NormalisableRange< float >                    ValueRange;

    static void addPeakFreqParamToLayout(ParamLayout& pl, PARAM_ID id);
    static void addPeakGainParamToLayout(ParamLayout& pl, PARAM_ID id);
    static void addPeakQualParamToLayout(ParamLayout& pl, PARAM_ID id);
    static void addEnabledParamToLayout(ParamLayout& pl, PARAM_ID id);
    static void addCutFreqParamToLayout(ParamLayout& pl, PARAM_ID id, const float default_value);
    static void addCutChoiceParamToLayout(ParamLayout& pl, PARAM_ID id);
    static void addShelfFreqParamToLayout(ParamLayout& pl, PARAM_ID id, const float default_value);
    static void addShelfGainParamToLayout(ParamLayout& pl, PARAM_ID id);
    static void addShelfQualParamToLayout(ParamLayout& pl, PARAM_ID id);

    static juce::ParameterID getVersionedParameterId(PARAM_ID id);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqParams)
};
