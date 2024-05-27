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
        //
        PEAK_0_FREQ,
        PEAK_0_GAIN,
        PEAK_0_Q,
        //
        HIGH_CUT_FREQ,
        HIGH_CUT_SLOPE,
    };

    static const std::map< PARAM_ID, juce::String > PARAM_NAME_MAP = {
        { LOW_CUT_FREQ, "Low Cut Freq" },
        { LOW_CUT_SLOPE, "Low Cut Slope" },
        //
        { PEAK_0_FREQ, "Peak 0 Freq" },
        { PEAK_0_GAIN, "Peak 0 Gain" },
        { PEAK_0_Q, "Peak 0 Q" },
        //
        { HIGH_CUT_FREQ, "High Cut Freq" },
        { HIGH_CUT_SLOPE, "High Cut Slope" },
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

}  // namespace EQ

}  // namespace Global
