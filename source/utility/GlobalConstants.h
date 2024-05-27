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

}  // namespace Global
