#include "AudioBufferFifo.h"

/*---------------------------------------------------------------------------
**
*/
AudioBufferFifo::AudioBufferFifo()
    : fifo_write_idx_(2)
    , fifo_read_idx_(0)
    , is_prepared_(false)
{
    std::fill(fifo_.begin(), fifo_.end(), juce::AudioBuffer< float >());
}

/*---------------------------------------------------------------------------
**
*/
void
AudioBufferFifo::prepare(const juce::dsp::ProcessSpec& process_spec)
{
    for (auto& buffer : fifo_) {
        buffer.setSize(static_cast< int >(process_spec.numChannels),
                       static_cast< int >(process_spec.maximumBlockSize),
                       false,
                       true,
                       true);
    }

    is_prepared_ = true;
}

/*---------------------------------------------------------------------------
**
*/
bool
AudioBufferFifo::isPrepared() const
{
    return is_prepared_;
}

/*---------------------------------------------------------------------------
**
*/
void
AudioBufferFifo::push(juce::AudioBuffer< float > buffer)
{
    if (!isPrepared()) {
        return;
    }

    // Buffers passed in by copy. We don't want to mutate the actual buffer
    // which has ultimately come from the audio thread.
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
juce::AudioBuffer< float >
AudioBufferFifo::pull() const
{
    return isPrepared() ? fifo_.at(fifo_read_idx_) : juce::AudioBuffer< float >();
}

/*---------------------------------------------------------------------------
** End of File
*/
