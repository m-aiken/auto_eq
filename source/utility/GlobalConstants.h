#pragma once

#include <JuceHeader.h>

namespace Global
{

static const float MAX_DB  = 12.f;
static const float NEG_INF = -48.f;

static const float MIN_HZ = 20.f;
static const float MAX_HZ = 20000.f;

static bool SHOW_DEBUG_BOUNDS = false;
static bool PROCESS_FFT       = true;

enum PATH_DISPLAY_MODE {
    PATH_STROKE,
    PATH_FILL,
};

static const uint8 ANALYSER_PADDING          = 32;
static const float ANALYSER_MARKER_FONT_SIZE = 12.f;

enum METER_TYPE {
    PEAK_METER,
    RMS_METER,
    LUFS_METER,
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

    static const juce::String getName(CHANNEL_ID channel_id)
    {
        return CHANNEL_NAME_MAP.at(channel_id);
    }

}  // namespace Channels

namespace FFT
{

    static const uint8 NUM_BUFFERS = 6;

    enum BUFFER_ID {
        PRIMARY_LEFT_PRE_EQ,
        PRIMARY_RIGHT_PRE_EQ,
        PRIMARY_LEFT_POST_EQ,
        PRIMARY_RIGHT_POST_EQ,
        SIDECHAIN_LEFT,
        SIDECHAIN_RIGHT,
    };

}  // namespace FFT

}  // namespace Global
