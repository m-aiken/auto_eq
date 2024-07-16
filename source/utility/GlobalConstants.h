#pragma once

#include <JuceHeader.h>

//#define TEST_FFT_ACCURACY 1
//#define SHOW_DEBUG_BOUNDS 1

namespace Global
{

static const float NEG_INF = -72.f;

static const float MAX_DB_BOOST = 12.f;
static const float MAX_DB_CUT   = -12.f;

static const float METER_MAX_DB  = 6.f;
static const float METER_NEG_INF = -48.f;

static const float FFT_MAX_DB  = 3.f;
static const float FFT_NEG_INF = -96.f;

static const float MIN_HZ = 20.f;
static const float MAX_HZ = 20000.f;

static const double BAND_MAGNITUDE_CALCULATION_FREQUENCY_MS = 20.0;
static const double FFT_PATH_PRODUCTION_FREQUENCY_MS        = 20.0;

static const uint8 ANALYSER_PADDING          = 32;
static const float ANALYSER_MARKER_FONT_SIZE = 12.f;

namespace Channels
{

    static const uint8 NUM_INPUTS  = 2;
    static const uint8 NUM_OUTPUTS = 2;

    enum CHANNEL_ID {
        INPUT_LEFT,
        INPUT_RIGHT,
    };

    static const std::map< CHANNEL_ID, juce::String > CHANNEL_NAME_MAP = {
        { INPUT_LEFT, "Input Left" },
        { INPUT_RIGHT, "Input Right" },
    };

    static const juce::String getName(CHANNEL_ID channel_id)
    {
        return CHANNEL_NAME_MAP.at(channel_id);
    }

}  // namespace Channels

namespace Meters
{

    enum METER_TYPE {
        PEAK_METER,
        RMS_METER,
        LUFS_METER,
    };

}  // namespace Meters

namespace FFT
{

    static const uint8 NUM_BUFFERS = 2;

    enum BUFFER_ID {
        LEFT_POST_EQ,
        RIGHT_POST_EQ,
    };

}  // namespace FFT

}  // namespace Global

namespace GuiParams
{

enum PARAM_ID {
    SHOW_FFT,
    ANALYSE_INPUT,
    FFT_ACCURACY_TEST_TONE_HZ,
    FFT_ACCURACY_TEST_TONE_DB,
};

static const std::map< PARAM_ID, juce::String > PARAM_NAME_MAP = {
    { SHOW_FFT, "SHOW_FFT" },
    { ANALYSE_INPUT, "ANALYSE_INPUT" },
    { FFT_ACCURACY_TEST_TONE_HZ, "FFT_ACCURACY_TEST_TONE_HZ" },
    { FFT_ACCURACY_TEST_TONE_DB, "FFT_ACCURACY_TEST_TONE_DB" },
};

static const juce::String
getName(PARAM_ID param_id)
{
    return PARAM_NAME_MAP.at(param_id);
}

}  // namespace GuiParams