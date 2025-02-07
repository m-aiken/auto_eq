#pragma once

#include <JuceHeader.h>

// #define TEST_FFT_ACCURACY 1
// #define SHOW_DEBUG_BOUNDS 1
#define ADD_TEST_PRESETS 1

namespace Global
{

static constexpr float NEG_INF = -72.f;

static constexpr float MAX_DB_BOOST = 12.f;
static constexpr float MAX_DB_CUT   = -12.f;

static constexpr float METER_MAX_DB  = 6.f;
static constexpr float METER_NEG_INF = -48.f;

static constexpr float FFT_MAX_DB  = 3.f;
static constexpr float FFT_NEG_INF = -96.f;

static constexpr float MIN_HZ = 20.f;
static constexpr float MAX_HZ = 20000.f;

static constexpr double BAND_MAGNITUDE_CALCULATION_FREQUENCY_MS = 20.0;
static constexpr double FFT_PATH_PRODUCTION_FREQUENCY_MS        = 20.0;

static constexpr uint8 GRAPH_TOP_PADDING = 32;
static constexpr uint8 METER_X_PADDING   = 32;
static constexpr uint8 METER_Y_PADDING   = 16;

namespace Channels
{

    static constexpr uint8 NUM_INPUTS  = 2;
    static constexpr uint8 NUM_OUTPUTS = 2;

    enum CHANNEL_ID {
        INPUT_LEFT,
        INPUT_RIGHT,
    };

    static const std::map< CHANNEL_ID, juce::String > CHANNEL_NAME_MAP = {
        { INPUT_LEFT, "Input Left" },
        { INPUT_RIGHT, "Input Right" },
    };

    static juce::String getName(const CHANNEL_ID channel_id) { return CHANNEL_NAME_MAP.at(channel_id); }

}  // namespace Channels

namespace Meters
{

    static constexpr uint8_t NUM_METERS = 5;

    enum METER_TYPE {
        INPUT_GAIN,
        OUTPUT_PEAK,
        OUTPUT_RMS,
        MOMENTARY_LOUDNESS,
        SHORT_TERM_LOUDNESS,
    };

    enum ORIENTATION {
        HORIZONTAL,
        VERTICAL,
    };

    static const std::map< METER_TYPE, juce::String > METER_NAME_MAP = {
        { INPUT_GAIN, "Input Gain" },                    //
        { OUTPUT_PEAK, "Output Peak" },                  //
        { OUTPUT_RMS, "Output RMS" },                    //
        { MOMENTARY_LOUDNESS, "Momentary Loudness" },    //
        { SHORT_TERM_LOUDNESS, "Short Term Loudness" },  //
    };

    static juce::String getName(const METER_TYPE meter_type) { return METER_NAME_MAP.at(meter_type); }

}  // namespace Meters

namespace FFT
{

    static constexpr uint8 NUM_BUFFERS = 2;

    enum BUFFER_ID {
        LEFT_POST_EQ,
        RIGHT_POST_EQ,
    };

}  // namespace FFT

}  // namespace Global

namespace GuiParams
{

static constexpr bool INITIAL_POWER_STATE        = true;
static constexpr bool INITIAL_ANALYSIS_STATE     = false;
static constexpr bool INITIAL_POWER_SAVING_STATE = false;
static constexpr bool INITIAL_UNITY_GAIN_STATE   = false;

static constexpr float INPUT_TRIM_MIN      = -24.f;
static constexpr float INPUT_TRIM_MAX      = 24.f;
static constexpr float INPUT_TRIM_INTERVAL = 0.1f;
static constexpr float INITIAL_INPUT_TRIM  = 0.f;

static constexpr float MASTER_GAIN_MIN      = -24.f;
static constexpr float MASTER_GAIN_MAX      = 12.f;
static constexpr float MASTER_GAIN_INTERVAL = 0.1f;
static constexpr float INITIAL_MASTER_GAIN  = 0.f;

enum PARAM_ID {
    POWER,
    ANALYSE_INPUT,
    POWER_SAVING,
    INPUT_TRIM,
    EQ_INTENSITY,
    MASTER_GAIN,
    UNITY_GAIN_ENABLED,
    FFT_ACCURACY_TEST_TONE_HZ,
    FFT_ACCURACY_TEST_TONE_DB,
};

static const std::map< PARAM_ID, juce::String > PARAM_NAME_MAP = {
    { POWER, "POWER" },
    { ANALYSE_INPUT, "ANALYSE_INPUT" },
    { POWER_SAVING, "POWER_SAVING" },
    { INPUT_TRIM, "INPUT_TRIM" },
    { EQ_INTENSITY, "EQ_INTENSITY" },
    { MASTER_GAIN, "MASTER_GAIN" },
    { UNITY_GAIN_ENABLED, "UNITY_GAIN_ENABLED" },
    { FFT_ACCURACY_TEST_TONE_HZ, "FFT_ACCURACY_TEST_TONE_HZ" },
    { FFT_ACCURACY_TEST_TONE_DB, "FFT_ACCURACY_TEST_TONE_DB" },
};

static juce::String
getName(const PARAM_ID param_id)
{
    return PARAM_NAME_MAP.at(param_id);
}

}  // namespace GuiParams

namespace PresetManagement
{

static constexpr uint8_t NUM_BUTTONS = 4;

enum BUTTON_ID {
    BUTTON_NEW,
    BUTTON_OPEN,
    BUTTON_SAVE,
    BUTTON_SAVE_AS,
};

static const std::map< BUTTON_ID, juce::String > BUTTON_TEXT_MAP = {
    { BUTTON_NEW, "New" },
    { BUTTON_OPEN, "Open" },
    { BUTTON_SAVE, "Save" },
    { BUTTON_SAVE_AS, "Save As" },
};

static juce::String
getButtonText(const BUTTON_ID button_id)
{
    return BUTTON_TEXT_MAP.at(button_id);
}

}  // namespace PresetManagement