#include "GlobalConstants.h"
#include "InputAnalysisFilter.h"

/*---------------------------------------------------------------------------
**
*/
InputAnalysisFilter::InputAnalysisFilter()
    : juce::Thread("THREAD_input_analysis_filter")
    , is_prepared_(false)
{
    initFilters();

    std::fill(band_buffers_.begin(), band_buffers_.end(), juce::AudioBuffer< float >());
    std::fill(band_adjustments_.begin(), band_adjustments_.end(), 0.f);
}

/*---------------------------------------------------------------------------
**
*/
InputAnalysisFilter::~InputAnalysisFilter()
{
    if (isThreadRunning()) {
        stopThread(ANALYSIS_FREQUENCY_MS);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::run()
{
    while (!threadShouldExit()) {
        processInputBuffer();

        wait(static_cast< double >(ANALYSIS_FREQUENCY_MS));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::prepare(const juce::dsp::ProcessSpec& process_spec)
{
    for (auto& band : filter_matrix_) {
        for (auto& filter : band) {
            filter.prepare(process_spec);
        }
    }

    for (auto& buffer : band_buffers_) {
        buffer.setSize(static_cast< int >(process_spec.numChannels),
                       static_cast< int >(process_spec.maximumBlockSize),
                       false,
                       true,
                       true);
    }

    fifo_.prepare(process_spec);

    is_prepared_ = true;
}

/*---------------------------------------------------------------------------
**
*/
bool
InputAnalysisFilter::isPrepared() const
{
    return (is_prepared_ && fifo_.isPrepared());
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::pushBufferForAnalysis(const juce::AudioBuffer< float >& buffer)
{
    if (fifo_.isPrepared()) {
        fifo_.push(buffer);
    }
}

/*---------------------------------------------------------------------------
**
*/
float
InputAnalysisFilter::getBandDbAdjustment(const Equalizer::BAND_ID band_id) const
{
    return band_adjustments_.at(band_id);
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::initFilters()
{
    using filter_type = juce::dsp::LinkwitzRileyFilterType;

    for (size_t bnd_idx = 0; bnd_idx < Equalizer::NUM_BANDS; ++bnd_idx) {
        const auto                                     band_id = static_cast< Equalizer::BAND_ID >(bnd_idx);
        InputAnalysisFilter::SingleBandFilterSequence& band_filter_sequence = filter_matrix_.at(band_id);
        const uint8 num_filters_needed = (band_id < 2) ? Equalizer::NUM_BANDS - 1 : Equalizer::NUM_BANDS - band_id;

        // The first filter in the sequence should be either:
        // * low pass for the first band
        // * high pass for all the other bands
        band_filter_sequence[0].setType(band_id == 0 ? filter_type::lowpass : filter_type::highpass);
        band_filter_sequence[0].setCutoffFrequency(Equalizer::getBandHz(band_id));

        if (num_filters_needed == 1) {
            // Band complete.
            continue;
        }

        // The rest of the filters in the sequence should be:
        // * low pass for the 2nd filter if NOT band zero
        // * all pass otherwise.
        for (uint8 flt_idx = 1; flt_idx < num_filters_needed; ++flt_idx) {
            const bool is_lowpass = (flt_idx == 1) && (band_id != 0);

            band_filter_sequence[flt_idx].setType(is_lowpass ? filter_type::lowpass : filter_type::allpass);
        }
    }
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::processInputBuffer()
{
    if (!isPrepared()) {
        return;
    }

    // Take by copy.
    const juce::AudioBuffer< float > input_buffer = fifo_.pull();

    for (auto& buffer : band_buffers_) {
        buffer.clear();
        buffer.makeCopyOf(input_buffer, true);
    }

    for (size_t band = 0; band < Equalizer::NUM_BANDS; ++band) {
        auto block   = juce::dsp::AudioBlock< float >(band_buffers_.at(band));
        auto context = juce::dsp::ProcessContextReplacing< float >(block);

        if (band == 0) {
            for (auto& filter : filter_matrix_.at(band)) {
                filter.process(context);
            }
        }
        else {
            filter_matrix_.at(band).at(Equalizer::B1).process(context);

            if (band != Equalizer::NUM_BANDS - 1) {
                band_buffers_.at(band + 1).makeCopyOf(band_buffers_.at(band), true);

                for (size_t lr_filter = Equalizer::B1; lr_filter < Equalizer::NUM_BANDS; ++lr_filter) {
                    filter_matrix_.at(band).at(lr_filter).process(context);
                }
            }
        }

        // Calculate the value to bring the current value to the target for this band.
        const auto  band_id  = static_cast< Equalizer::BAND_ID >(band);
        const float input_db = getBandInputDb(band_id);

        if (input_db == Global::NEG_INF) {
            // If the input dB for this band is essentially silent skip this band.
            band_adjustments_.at(band) = 0.f;
        }
        else {
            const float target_db      = Equalizer::getBandTargetDb(band_id);
            band_adjustments_.at(band) = (target_db - input_db);
        }
    }

    //    printBandMagnitudesPreProcessing();
}

/*---------------------------------------------------------------------------
**
*/
float
InputAnalysisFilter::getBandInputDb(const Equalizer::BAND_ID band_id) const
{
    const juce::AudioBuffer< float >& buffer      = band_buffers_.at(band_id);
    const int                         num_samples = buffer.getNumSamples();

    const float rms_l = buffer.getRMSLevel(Global::Channels::INPUT_LEFT, 0, num_samples);
    const float rms_r = buffer.getRMSLevel(Global::Channels::INPUT_RIGHT, 0, num_samples);

    return juce::Decibels::gainToDecibels(std::max(rms_l, rms_r), Global::NEG_INF);
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::printBandMagnitudesPreProcessing() const
{
    DBG("--------------------------------------------------");

    for (size_t band = 0; band < Equalizer::NUM_BANDS; ++band) {
        const float val = getBandInputDb(static_cast< Equalizer::BAND_ID >(band));
        DBG("B" + juce::String(band + 1) + ": " + juce::String(val));
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
