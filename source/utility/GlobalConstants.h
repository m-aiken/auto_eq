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
    PLAYBACK_LEFT,
    PLAYBACK_RIGHT,
    AMBIENT_LEFT,
    AMBIENT_RIGHT,
};

}  // namespace Global
