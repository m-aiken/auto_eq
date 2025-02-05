#include "BandUpdater.h"
#include "GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
BandUpdater::BandUpdater(InputAnalysisFilter& analysis_filter)
    : juce::Thread("THREAD_band_updater")
    , analysis_filter_(analysis_filter)
    , is_prepared_(false)
{
}

/*---------------------------------------------------------------------------
**
*/
BandUpdater::~BandUpdater()
{
    if (isThreadRunning()) {
        stopThread(UPDATE_FREQUENCY_MS);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
BandUpdater::prepare(const double sample_rate)
{
    for (auto& band : band_values_array_) {
        band.reset(sample_rate, BAND_DB_RAMP_TIME_SECONDS);
        band.setCurrentAndTargetValue(0.f);
    }

    is_prepared_ = true;
}

/*---------------------------------------------------------------------------
**
*/
bool
BandUpdater::isPrepared() const
{
    return is_prepared_;
}

/*---------------------------------------------------------------------------
**
*/
void
BandUpdater::run()
{
    while (!threadShouldExit()) {
        updateBandValues();

        wait(static_cast< double >(UPDATE_FREQUENCY_MS));
    }
}

/*---------------------------------------------------------------------------
**
*/
float
BandUpdater::getBandDb(const Equalizer::BAND_ID band_id)
{
    BandUpdater::SmoothedFloat& sf = band_values_array_.at(band_id);

    return isThreadRunning() ? sf.getNextValue() : sf.getCurrentValue();
}

/*---------------------------------------------------------------------------
**
*/
void
BandUpdater::syncroniseWithTreeState(const juce::AudioProcessorValueTreeState& apvts)
{
    for (size_t i = 0; i < band_values_array_.size(); ++i) {
        const auto                        band_id     = static_cast< Equalizer::BAND_ID >(i);
        const juce::RangedAudioParameter* apvts_param = apvts.getParameter(Equalizer::getBandName(band_id));

        if (apvts_param == nullptr) {
            continue;
        }

        const float db_value = apvts_param->convertFrom0to1(apvts_param->getValue());

        band_values_array_.at(band_id).setCurrentAndTargetValue(db_value);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
BandUpdater::updateBandValues()
{
    //    printBandAdjustments();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID band_id = static_cast< Equalizer::BAND_ID >(i);
        float              db_val  = analysis_filter_.getBandDbAdjustment(band_id);

        db_val = (db_val >= 0) ? std::min(db_val, Global::MAX_DB_BOOST) : std::max(db_val, Global::MAX_DB_CUT);

        band_values_array_.at(band_id).setTargetValue(db_val);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
BandUpdater::printBandAdjustments()
{
    DBG("--------------------------------------------------");

    for (size_t band = 0; band < Equalizer::NUM_BANDS; ++band) {
        float val = analysis_filter_.getBandDbAdjustment(static_cast< Equalizer::BAND_ID >(band));

        val = (val >= 0) ? std::min(val, Global::MAX_DB_BOOST) : std::max(val, Global::MAX_DB_CUT);

        DBG("B" + juce::String(band + 1) + ": " + juce::String(val));
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
