#include "MonoFftBuffer.h"

/*---------------------------------------------------------------------------
**
*/
MonoFftBuffer::MonoFftBuffer()
    : sample_rate_(0.0)
    , buffer_index_(0)
    , is_prepared_(false)
{
    std::fill(ring_buffer_.begin(), ring_buffer_.end(), 0.f);
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftBuffer::prepare(double sample_rate)
{
    sample_rate_ = sample_rate;
    is_prepared_ = true;
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftBuffer::pushNextSample(float sample)
{
    ring_buffer_.at(buffer_index_) = sample;

    ++buffer_index_;

    if (buffer_index_ == FFT_SIZE) {
        buffer_index_ = 0;
    }
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftBuffer::getNextBlock(FftDataBlock& block) const
{
    // Zero out the incoming buffer.
    std::fill(block.begin(), block.end(), 0.f);
    // Fill the first half with our ring buffer's samples.
    std::copy(ring_buffer_.begin(), ring_buffer_.end(), block.begin());
}

/*---------------------------------------------------------------------------
**
*/
double
MonoFftBuffer::getBinWidth() const
{
    return isPrepared() ? (sample_rate_ / static_cast< double >(FFT_SIZE)) : 0.0;
}

/*---------------------------------------------------------------------------
**
*/
bool
MonoFftBuffer::isPrepared() const
{
    return is_prepared_;
}

/*---------------------------------------------------------------------------
** End of File
*/
