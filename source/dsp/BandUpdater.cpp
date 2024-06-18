#include "BandUpdater.h"

/*static*/ const uint16 BandUpdater::UPDATE_FREQUENCY_MS = 1000;

/*---------------------------------------------------------------------------
**
*/
BandUpdater::BandUpdater(InputAnalysisFilter& analysis_filter, juce::AudioProcessorValueTreeState& apvts)
    : juce::Thread("THREAD_band_updater")
    , analysis_filter_(analysis_filter)
    , apvts_(apvts)
{
    startThread();
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
BandUpdater::updateBandValues()
{
    //    printBandAdjustments();

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID band_id = static_cast< Equalizer::BAND_ID >(i);

        juce::AudioParameterFloat* param = getBandParameter(band_id);

        if (param != nullptr) {
            float adjustment = analysis_filter_.getBandDbAdjustment(band_id);

            adjustment = (adjustment >= 0) ? std::min(adjustment, Equalizer::MAX_BAND_DB_BOOST) :
                                             std::max(adjustment, Equalizer::MAX_BAND_DB_CUT);

            *param = adjustment;
        }
    }
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioParameterFloat*
BandUpdater::getBandParameter(Equalizer::BAND_ID band_id)
{
    return dynamic_cast< juce::AudioParameterFloat* >(apvts_.getParameter(Equalizer::getBandName(band_id)));
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

        val = (val >= 0) ? std::min(val, Equalizer::MAX_BAND_DB_BOOST) : std::max(val, Equalizer::MAX_BAND_DB_CUT);

        DBG("B" + juce::String(band + 1) + ": " + juce::String(val));
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
