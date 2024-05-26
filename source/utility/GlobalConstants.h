#pragma once

#include <JuceHeader.h>

namespace Global
{

static const float MAX_DB  = 12.f;
static const float NEG_INF = -48.f;

static const float MIN_HZ = 20.f;
static const float MAX_HZ = 20000.f;

static const uint8 NUM_INPUTS = 4;

enum CHANNEL_DESIGNATION {
    CHANNEL_PLAYBACK_LEFT,
    CHANNEL_PLAYBACK_RIGHT,
    CHANNEL_AMBIENT_LEFT,
    CHANNEL_AMBIENT_RIGHT,
};

}  // namespace Global
