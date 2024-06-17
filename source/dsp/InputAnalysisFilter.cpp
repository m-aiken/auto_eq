#include "InputAnalysisFilter.h"
#include "../utility/GlobalConstants.h"

/*static*/ const uint16 InputAnalysisFilter::ANALYSIS_FREQUENCY_MS = 200;

/*---------------------------------------------------------------------------
**
*/
InputAnalysisFilter::InputAnalysisFilter(const juce::AudioProcessorValueTreeState& apvts)
    : juce::Thread("THREAD_input_analysis_filter")
    , fifo_write_idx_(1)
    , fifo_read_idx_(0)
    , apvts_(apvts)
    , is_prepared_(false)
{
    initFilters();

    std::fill(band_buffers_.begin(), band_buffers_.end(), juce::AudioBuffer< float >());
    std::fill(band_adjustments_.begin(), band_adjustments_.end(), 0.f);
    std::fill(fifo_.begin(), fifo_.end(), juce::AudioBuffer< float >());
}

/*---------------------------------------------------------------------------
**
*/
InputAnalysisFilter::~InputAnalysisFilter()
{
    stopThread(ANALYSIS_FREQUENCY_MS);
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::run()
{
    while (!threadShouldExit()) {
        processInputBuffer();
        updateBandValues();

        wait(ANALYSIS_FREQUENCY_MS);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::prepare(juce::dsp::ProcessSpec& process_spec)
{
    for (auto& band : filter_matrix_) {
        for (auto& filter : band) {
            filter.prepare(process_spec);
        }
    }

    for (auto& buffer : band_buffers_) {
        buffer.setSize(process_spec.numChannels, process_spec.maximumBlockSize, false, true, true);
    }

    for (auto& buffer : fifo_) {
        buffer.setSize(process_spec.numChannels, process_spec.maximumBlockSize, false, true, true);
    }

    is_prepared_ = true;

    startThread();
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::pushBufferForAnalysis(juce::AudioBuffer< float > buffer)
{
    // Buffers passed in by copy. We don't want to mutate the actual buffer.
    std::swap(fifo_.at(fifo_write_idx_), buffer);

    if (++fifo_write_idx_ == FIFO_SIZE) {
        fifo_write_idx_ = 0;
    }

    if (++fifo_read_idx_ == FIFO_SIZE) {
        fifo_read_idx_ = 0;
    }
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::initFilters()
{
    using filter_type = juce::dsp::LinkwitzRileyFilterType;

    for (size_t bnd_idx = 0; bnd_idx < Equalizer::NUM_BANDS; ++bnd_idx) {
        Equalizer::BAND_ID                             band_id = static_cast< Equalizer::BAND_ID >(bnd_idx);
        InputAnalysisFilter::SingleBandFilterSequence& band_filter_sequence = filter_matrix_.at(band_id);
        uint8 num_filters_needed = (band_id < 2) ? Equalizer::NUM_BANDS - 1 : Equalizer::NUM_BANDS - band_id;

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
            bool is_lowpass = (flt_idx == 1) && (band_id != 0);

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
    if (!is_prepared_) {
        return;
    }

    // Take by copy.
    const juce::AudioBuffer< float > input_buffer = fifo_.at(fifo_read_idx_);

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
        Equalizer::BAND_ID band_id = static_cast< Equalizer::BAND_ID >(band);

        float target_db = Equalizer::getBandTargetDb(band_id);
        float input_db  = getBandInputDb(band_id);

        band_adjustments_.at(band) = (target_db - input_db);
    }

    //    printBandMagnitudesPreProcessing();
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::updateBandValues()
{
    //    printBandAdjustments();
    //    DBG("--------------------------------------------------");

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        Equalizer::BAND_ID band_id = static_cast< Equalizer::BAND_ID >(i);

        juce::AudioParameterFloat* param = getBandParameter(band_id);

        if (param != nullptr) {
            float adjustment = getBandDbAdjustment(band_id);

            adjustment = (adjustment >= 0) ? std::min(adjustment, Equalizer::MAX_BAND_DB_BOOST) :
                                             std::max(adjustment, Equalizer::MAX_BAND_DB_CUT);

            //            DBG("B" + juce::String(i + 1) + ": " + juce::String(adjustment));

            *param = adjustment;
        }
    }
}

/*---------------------------------------------------------------------------
**
*/
float
InputAnalysisFilter::getBandInputDb(Equalizer::BAND_ID band_id) const
{
    const juce::AudioBuffer< float >& buffer      = band_buffers_.at(band_id);
    const int                         num_samples = buffer.getNumSamples();

    const float rms_l = buffer.getRMSLevel(Global::Channels::PRIMARY_LEFT, 0, num_samples);
    const float rms_r = buffer.getRMSLevel(Global::Channels::PRIMARY_RIGHT, 0, num_samples);

    return juce::Decibels::gainToDecibels(std::max(rms_l, rms_r), Global::NEG_INF);
}

/*---------------------------------------------------------------------------
**
*/
float
InputAnalysisFilter::getBandDbAdjustment(Equalizer::BAND_ID band_id) const
{
    return band_adjustments_.at(band_id);
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioParameterFloat*
InputAnalysisFilter::getBandParameter(Equalizer::BAND_ID band_id)
{
    return dynamic_cast< juce::AudioParameterFloat* >(apvts_.getParameter(Equalizer::getBandName(band_id)));
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::printBandMagnitudesPreProcessing()
{
    DBG("--------------------------------------------------");

    for (size_t band = 0; band < Equalizer::NUM_BANDS; ++band) {
        float val = getBandInputDb(static_cast< Equalizer::BAND_ID >(band));
        DBG("B" + juce::String(band + 1) + ": " + juce::String(val));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
InputAnalysisFilter::printBandAdjustments()
{
    DBG("--------------------------------------------------");

    for (size_t band = 0; band < Equalizer::NUM_BANDS; ++band) {
        float val = getBandDbAdjustment(static_cast< Equalizer::BAND_ID >(band));
        DBG("B" + juce::String(band + 1) + ": " + juce::String(val));
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
