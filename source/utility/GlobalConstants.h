#pragma once

#include <JuceHeader.h>

namespace Global
{

static const float MAX_DB  = 12.f;
static const float NEG_INF = -48.f;

static const float MIN_HZ = 20.f;
static const float MAX_HZ = 20000.f;

enum PATH_DISPLAY_MODE {
    PATH_STROKE,
    PATH_FILL,
};

namespace Channels
{

    static const uint8 NUM_INPUTS  = 4;
    static const uint8 NUM_OUTPUTS = 2;

    enum CHANNEL_ID {
        PRIMARY_LEFT,
        PRIMARY_RIGHT,
        SIDECHAIN_LEFT,
        SIDECHAIN_RIGHT,
    };

    static const std::map< CHANNEL_ID, juce::String > CHANNEL_NAME_MAP = {
        { PRIMARY_LEFT, "Primary Input Left" },
        { PRIMARY_RIGHT, "Primary Input Right" },
        { SIDECHAIN_LEFT, "Sidechain Input Left" },
        { SIDECHAIN_RIGHT, "Sidechain Input Right" },
    };

    static const juce::String getChannelName(CHANNEL_ID channel_id)
    {
        return CHANNEL_NAME_MAP.at(channel_id);
    }

}  // namespace Channels

namespace EQ
{
    static const float MIN_Q     = 0.1f;
    static const float MAX_Q     = 10.f;
    static const float DEFAULT_Q = 1.f;

    enum PARAM_ID {
        LOW_CUT_FREQ,
        LOW_CUT_SLOPE,
        LOW_CUT_ENABLED,
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
        PEAK_6_FREQ,
        PEAK_6_GAIN,
        PEAK_6_Q,
        //
        HIGH_CUT_FREQ,
        HIGH_CUT_SLOPE,
        HIGH_CUT_ENABLED,
    };

    static const std::map< PARAM_ID, juce::String > PARAM_NAME_MAP = {
        { LOW_CUT_FREQ, "Low Cut Freq" },
        { LOW_CUT_SLOPE, "Low Cut Slope" },
        { LOW_CUT_ENABLED, "Low Cut Enabled" },
        //
        { PEAK_1_FREQ, "Peak 1 Freq" },
        { PEAK_1_GAIN, "Peak 1 Gain" },
        { PEAK_1_Q, "Peak 1 Q" },
        //
        { PEAK_2_FREQ, "Peak 2 Freq" },
        { PEAK_2_GAIN, "Peak 2 Gain" },
        { PEAK_2_Q, "Peak 2 Q" },
        //
        { PEAK_3_FREQ, "Peak 3 Freq" },
        { PEAK_3_GAIN, "Peak 3 Gain" },
        { PEAK_3_Q, "Peak 3 Q" },
        //
        { PEAK_4_FREQ, "Peak 4 Freq" },
        { PEAK_4_GAIN, "Peak 4 Gain" },
        { PEAK_4_Q, "Peak 4 Q" },
        //
        { PEAK_5_FREQ, "Peak 5 Freq" },
        { PEAK_5_GAIN, "Peak 5 Gain" },
        { PEAK_5_Q, "Peak 5 Q" },
        //
        { PEAK_6_FREQ, "Peak 6 Freq" },
        { PEAK_6_GAIN, "Peak 6 Gain" },
        { PEAK_6_Q, "Peak 6 Q" },
        //
        { HIGH_CUT_FREQ, "High Cut Freq" },
        { HIGH_CUT_SLOPE, "High Cut Slope" },
        { HIGH_CUT_ENABLED, "High Cut Enabled" },
    };

    static const juce::String getParamName(PARAM_ID param_id)
    {
        return PARAM_NAME_MAP.at(param_id);
    }

    enum SLOPE_CHOICE {
        DB_PER_OCT_12,
        DB_PER_OCT_24,
        DB_PER_OCT_36,
        DB_PER_OCT_48,
    };

    static juce::StringArray getSlopeChoices()
    {
        return juce::StringArray("12dB/Oct", "24dB/Oct", "36dB/Oct", "48dB/Oct");
    }

    static float getDefaultPeakFrequency(PARAM_ID param_id)
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

        return NEG_INF;
    }

    typedef juce::AudioProcessorValueTreeState::ParameterLayout ParamLayout;
    typedef juce::NormalisableRange< float >                    ValueRange;

    static void addPeakFreqParamToLayout(ParamLayout& pl, PARAM_ID id)
    {
        ValueRange range(MIN_HZ, MAX_HZ, 1.f, 1.f);
        pl.add(std::make_unique< juce::AudioParameterFloat >(id, getParamName(id), range, getDefaultPeakFrequency(id)));
    }

    static void addPeakGainParamToLayout(ParamLayout& pl, PARAM_ID id)
    {
        ValueRange range(NEG_INF, MAX_DB, 0.5f, 1.f);
        pl.add(std::make_unique< juce::AudioParameterFloat >(id, getParamName(id), range, 0.f));
    }

    static void addPeakQualParamToLayout(ParamLayout& pl, PARAM_ID id)
    {
        ValueRange range(MIN_Q, MAX_Q, 0.05f, 1.f);
        pl.add(std::make_unique< juce::AudioParameterFloat >(id, getParamName(id), range, DEFAULT_Q));
    }

    static void addEnabledParamToLayout(ParamLayout& pl, PARAM_ID id)
    {
        pl.add(std::make_unique< juce::AudioParameterBool >(id, getParamName(id), false));
    }

    static void addCutFreqParamToLayout(ParamLayout& pl, PARAM_ID id, const float default_value)
    {
        ValueRange range(MIN_HZ, MAX_HZ, 1.f, 1.f);
        pl.add(std::make_unique< juce::AudioParameterFloat >(id, getParamName(id), range, default_value));
    }

    static void addCutChoiceParamToLayout(ParamLayout& pl, PARAM_ID id)
    {
        pl.add(std::make_unique< juce::AudioParameterChoice >(id, getParamName(id), getSlopeChoices(), DB_PER_OCT_12));
    }

}  // namespace EQ

}  // namespace Global
