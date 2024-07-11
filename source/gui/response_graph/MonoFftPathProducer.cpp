#include "MonoFftPathProducer.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
MonoFftPathProducer::MonoFftPathProducer(MonoFftBuffer& fft_buffer)
    : juce::Thread("THREAD_mono_fft_path_producer")
    , fifo_write_idx_(2)
    , fifo_read_idx_(0)
    , fft_(MonoFftBuffer::FFT_ORDER)
    , windowing_fn_(MonoFftBuffer::FFT_SIZE, juce::dsp::WindowingFunction< float >::rectangular)
    , fft_buffer_(fft_buffer)
    , drawable_bounds_(0, 0, 0, 0)
{
    std::fill(fft_data_.begin(), fft_data_.end(), 0.f);
}

/*---------------------------------------------------------------------------
**
*/
MonoFftPathProducer::~MonoFftPathProducer()
{
    stopThread(static_cast< int >(Global::FFT_PATH_PRODUCTION_FREQUENCY_MS));
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPathProducer::prepare(const juce::Rectangle< int >& bounds)
{
    // This method gets called by the owning GUI class from its resized method.
    // It will be called any time the parent widget resizes.
    // Multiple calls to startThread don't matter.
    // If the thread is already running startThread does nothing.
    drawable_bounds_ = bounds;

    startThread();
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPathProducer::run()
{
    while (!threadShouldExit()) {
        processFftData();
        generatePath();

        if (++fifo_write_idx_ == FIFO_SIZE) {
            fifo_write_idx_ = 0;
        }

        if (++fifo_read_idx_ == FIFO_SIZE) {
            fifo_read_idx_ = 0;
        }

        wait(Global::FFT_PATH_PRODUCTION_FREQUENCY_MS);
    }
}

/*---------------------------------------------------------------------------
**
*/
juce::Path&
MonoFftPathProducer::getPath()
{
    return fifo_.at(fifo_read_idx_);
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPathProducer::processFftData()
{
    fft_buffer_.getNextBlock(fft_data_);
    windowing_fn_.multiplyWithWindowingTable(fft_data_.data(), MonoFftBuffer::FFT_SIZE);
    fft_.performFrequencyOnlyForwardTransform(fft_data_.data(), true);

    juce::FloatVectorOperations::multiply(fft_data_.data(),
                                          1.f / static_cast< float >(MonoFftBuffer::NUM_BINS),
                                          MonoFftBuffer::NUM_BINS + 1);

    for (size_t i = 0; i < fft_data_.size(); ++i) {
        fft_data_.at(i) = juce::Decibels::gainToDecibels(fft_data_.at(i), Global::FFT_NEG_INF);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPathProducer::generatePath()
{
    auto   bounds_x      = drawable_bounds_.getX();
    auto   bounds_width  = drawable_bounds_.getWidth();
    auto   bounds_height = drawable_bounds_.getHeight();
    size_t num_bins      = MonoFftBuffer::NUM_BINS;
    float  bin_width     = static_cast< float >(fft_buffer_.getBinWidth());

    auto y_coord = getYCoordinate(fft_data_.at(0));

    if (std::isnan(y_coord) || std::isinf(y_coord)) {
        y_coord = bounds_height;
    }

    juce::Path& path = fifo_.at(fifo_write_idx_);

    path.clear();
    path.startNewSubPath(bounds_x, bounds_height);

    const uint8 path_resolution = 2;

    for (size_t i = 1; i < num_bins + 1; i += path_resolution) {
        y_coord = getYCoordinate(fft_data_.at(i));

        if (std::isnan(y_coord) || std::isinf(y_coord)) {
            continue;
        }

        auto raw_freq        = i * bin_width;
        auto normalised_freq = juce::mapFromLog10(raw_freq, Global::MIN_HZ, Global::MAX_HZ);
        auto x_coord         = std::floor(normalised_freq * bounds_width);

        if (x_coord > bounds_width) {
            continue;
        }

        path.lineTo(x_coord, y_coord);
    }

    path.lineTo(bounds_width, bounds_height);
    path.closeSubPath();
}

/*---------------------------------------------------------------------------
**
*/
float
MonoFftPathProducer::getYCoordinate(const float& sample)
{
    auto bounds_y      = drawable_bounds_.getY();
    auto bounds_height = drawable_bounds_.getHeight();

    return juce::jmap< float >(sample, Global::FFT_NEG_INF, Global::FFT_MAX_DB, bounds_height, bounds_y);
}

/*---------------------------------------------------------------------------
** End of File
*/
