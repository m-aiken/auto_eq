#include "MonoFftPath.h"

/*---------------------------------------------------------------------------
**
*/
MonoFftPath::MonoFftPath(MonoFftBuffer&              fft_buffer,
                         Theme::DarkLightPair        path_colour,
                         Global::PATH_DISPLAY_MODE   display_mode,
                         juce::RangedAudioParameter* fft_enablement_param)
    : fft_(MonoFftBuffer::FFT_ORDER)
    , windowing_fn_(MonoFftBuffer::FFT_SIZE, juce::dsp::WindowingFunction< float >::blackmanHarris)
    , fft_buffer_(fft_buffer)
    , path_colour_(path_colour)
    , display_mode_(display_mode)
    , fft_enablement_param_(fft_enablement_param)
{
    std::fill(fft_data_.begin(), fft_data_.end(), 0.f);

    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
MonoFftPath::~MonoFftPath()
{
    stopTimer();
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPath::paint(juce::Graphics& g)
{
    //    if (path_.isEmpty()) {
    //        return;
    //    }

    g.setColour(Theme::getColour(path_colour_));

    if (display_mode_ == Global::PATH_STROKE) {
        g.strokePath(path_, juce::PathStrokeType(1.f));
    }
    else {
        g.fillPath(path_);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPath::timerCallback()
{
    if (fft_enablement_param_ != nullptr && fft_enablement_param_->getValue()) {
        processFftData();
        generatePath();
    }
    else {
        path_.clear();
    }

    repaint();
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPath::processFftData()
{
    fft_buffer_.getNextBlock(fft_data_);
    windowing_fn_.multiplyWithWindowingTable(fft_data_.data(), MonoFftBuffer::FFT_SIZE);
    fft_.performFrequencyOnlyForwardTransform(fft_data_.data(), true);

    juce::FloatVectorOperations::multiply(fft_data_.data(),
                                          1.f / static_cast< float >(MonoFftBuffer::NUM_BINS),
                                          MonoFftBuffer::NUM_BINS + 1);

    for (size_t i = 0; i < fft_data_.size(); ++i) {
        fft_data_.at(i) = juce::Decibels::gainToDecibels(fft_data_.at(i), Global::MAX_DB_CUT);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPath::generatePath()
{
    auto   bounds        = getLocalBounds();
    auto   bounds_x      = bounds.getX();
    auto   bounds_y      = bounds.getY();
    auto   bounds_width  = bounds.getWidth();
    auto   bounds_height = bounds.getHeight();
    size_t num_bins      = MonoFftBuffer::NUM_BINS;
    float  bin_width     = static_cast< float >(fft_buffer_.getBinWidth());

    auto y_coord = getYCoordinate(fft_data_.at(0));

    if (std::isnan(y_coord) || std::isinf(y_coord)) {
        y_coord = bounds_height;
    }

    path_.clear();
    path_.startNewSubPath(bounds_x, bounds_height);

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

        path_.lineTo(x_coord, y_coord);
    }

    path_.lineTo(bounds_width, bounds_height);
    path_.closeSubPath();
}

/*---------------------------------------------------------------------------
**
*/
float
MonoFftPath::getYCoordinate(const float& sample)
{
    auto bounds        = getLocalBounds();
    auto bounds_y      = bounds.getY();
    auto bounds_height = bounds.getHeight();

    return juce::jmap< float >(sample, Global::MAX_DB_CUT, Global::MAX_DB_BOOST, bounds_height, bounds_y);
}

/*---------------------------------------------------------------------------
** End of File
*/
