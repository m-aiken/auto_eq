#include "BandUpdater.h"
#include "../utility/GlobalConstants.h"

/*static*/ const uint16 BandUpdater::UPDATE_FREQUENCY_MS = 1000;

/*---------------------------------------------------------------------------
**
*/
BandUpdater::BandUpdater(InputAnalysisFilter& analysis_filter, BandDbValueArray& band_values_array)
    : juce::Thread("THREAD_band_updater")
    , analysis_filter_(analysis_filter)
    , band_values_array_(band_values_array)
{
    // We don't start the new thread immediately because the band values contains
    // juce::SmoothedValue<float> (not raw float) which need special preparation.
    // That preparation happens in PluginProcessor::prepareToPlay() after which our
    // startPolling() method is called.
}

/*---------------------------------------------------------------------------
**
*/
BandUpdater::~BandUpdater()
{
    stopThread(UPDATE_FREQUENCY_MS);
}

/*---------------------------------------------------------------------------
**
*/
void
BandUpdater::run()
{
    while (!threadShouldExit()) {
        updateBandValues();

        wait(UPDATE_FREQUENCY_MS);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
BandUpdater::startPolling()
{
    startThread();
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
