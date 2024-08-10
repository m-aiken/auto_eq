#include "GlobalConstants.h"
#include "UnityGainCalculator.h"

/*static*/ const uint16 UnityGainCalculator::CALCULATION_FREQUENCY_MS = 1000;
/*static*/ const double UnityGainCalculator::RAMP_TIME_SECONDS        = 0.001;

/*---------------------------------------------------------------------------
**
*/
UnityGainCalculator::UnityGainCalculator(juce::RangedAudioParameter* master_gain_param)
    : juce::Thread("THREAD_unity_gain_calculator")
    , master_gain_param_(master_gain_param)
    , fifo_size_(0)
    , is_prepared_(false)
{
    write_indexes_.at(PRE_PROCESSED_FIFO)  = 1;
    read_indexes_.at(PRE_PROCESSED_FIFO)   = 0;
    write_indexes_.at(POST_PROCESSED_FIFO) = 1;
    read_indexes_.at(POST_PROCESSED_FIFO)  = 0;
}

/*---------------------------------------------------------------------------
**
*/
UnityGainCalculator::~UnityGainCalculator()
{
    if (isThreadRunning()) {
        stopThread(CALCULATION_FREQUENCY_MS);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
UnityGainCalculator::run()
{
    if (!isPrepared()) {
        return;
    }

    while (!threadShouldExit()) {
        calculateNextTargetValue();

        wait(static_cast< double >(CALCULATION_FREQUENCY_MS));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
UnityGainCalculator::prepare(double sample_rate, uint32 samples_per_callback)
{
    // Set the 2 magnitude buffers to the correct size for one second.
    size_t num_callbacks_per_second = static_cast< size_t >(std::floor(sample_rate / samples_per_callback));

    magnitude_fifos_.at(PRE_PROCESSED_FIFO).resize(num_callbacks_per_second, 0.f);
    magnitude_fifos_.at(POST_PROCESSED_FIFO).resize(num_callbacks_per_second, 0.f);

    fifo_size_ = num_callbacks_per_second;

    unity_gain_adjustment_.reset(sample_rate, RAMP_TIME_SECONDS);
    unity_gain_adjustment_.setCurrentAndTargetValue(0.f);

    is_prepared_ = true;
}

/*---------------------------------------------------------------------------
**
*/
bool
UnityGainCalculator::isPrepared() const
{
    return is_prepared_;
}

/*---------------------------------------------------------------------------
**
*/
void
UnityGainCalculator::pushForAnalysis(const juce::AudioBuffer< float >& buffer, FIFO_ID fifo_id)
{
    if (!isPrepared()) {
        return;
    }

    magnitude_fifos_.at(fifo_id).at(write_indexes_.at(fifo_id)) = buffer.getMagnitude(0, buffer.getNumSamples());

    if (++write_indexes_.at(fifo_id) == fifo_size_) {
        write_indexes_.at(fifo_id) = 0;
    }

    if (++read_indexes_.at(fifo_id) == fifo_size_) {
        read_indexes_.at(fifo_id) = 0;
    }
}

/*---------------------------------------------------------------------------
**
*/
float
UnityGainCalculator::getGainAdjustment()
{
    if (master_gain_param_ == nullptr) {
        return 0.f;
    }

    float adjustment        = unity_gain_adjustment_.getNextValue();
    float adjustment_scaled = juce::jmap< float >(adjustment, -1.f, 1.f, Global::MAX_DB_CUT, Global::MAX_DB_BOOST);
    float adjustment_norm   = master_gain_param_->convertTo0to1(adjustment_scaled);

    return adjustment_norm;
}

/*---------------------------------------------------------------------------
**
*/
void
UnityGainCalculator::calculateNextTargetValue()
{
    auto float2dp = [](float a) -> float { return std::round(std::round(a * 1000.f) / 10.f) / 100.f; };

    float pre  = magnitude_fifos_.at(PRE_PROCESSED_FIFO).at(read_indexes_.at(PRE_PROCESSED_FIFO));
    float post = magnitude_fifos_.at(POST_PROCESSED_FIFO).at(read_indexes_.at(POST_PROCESSED_FIFO));

    pre  = float2dp(pre);
    post = float2dp(post);

    float adjustment = (pre - post);

    unity_gain_adjustment_.setTargetValue(adjustment);
}

/*---------------------------------------------------------------------------
** End of File
*/
