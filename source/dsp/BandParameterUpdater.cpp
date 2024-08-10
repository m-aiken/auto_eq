#include "BandParameterUpdater.h"
#include "Equalizer.h"

/*static*/ const uint16 BandParameterUpdater::UPDATE_FREQUENCY_MS = 20;

/*---------------------------------------------------------------------------
**
*/
BandParameterUpdater::BandParameterUpdater(juce::AudioProcessorValueTreeState& apvts, BandUpdater& band_updater)
    : juce::Thread("THREAD_band_parameter_updater")
    , apvts_(apvts)
    , band_updater_(band_updater)
{
}

/*---------------------------------------------------------------------------
**
*/
BandParameterUpdater::~BandParameterUpdater()
{
    if (isThreadRunning()) {
        stopThread(UPDATE_FREQUENCY_MS);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
BandParameterUpdater::run()
{
    while (!threadShouldExit()) {
        updateParameters();

        wait(static_cast< double >(UPDATE_FREQUENCY_MS));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
BandParameterUpdater::updateParameters()
{
    if (!band_updater_.isThreadRunning()) {
        return;
    }

    // We're changing the band parameter values which will have a side effect of
    // triggering the band sliders to repaint on the message thread.
    // We need to acquire a lock for the message thread whilst doing so.
    // The lock is scoped, hence putting it on the stack.
    const juce::MessageManagerLock message_manager_lock;

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID          band_id      = static_cast< Equalizer::BAND_ID >(i);
        juce::String                parameter_id = Equalizer::getBandName(band_id);
        juce::RangedAudioParameter* apvts_param  = apvts_.getParameter(parameter_id);

        if (apvts_param == nullptr) {
            continue;
        }

        float db_value = band_updater_.getBandDb(band_id);

        apvts_param->beginChangeGesture();
        apvts_param->setValueNotifyingHost(apvts_param->convertTo0to1(db_value));
        apvts_param->endChangeGesture();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
