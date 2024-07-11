#include "MonoFftPath.h"

/*---------------------------------------------------------------------------
**
*/
MonoFftPath::MonoFftPath(MonoFftBuffer&              fft_buffer,
                         Theme::DarkLightPair        path_colour,
                         Global::PATH_DISPLAY_MODE   display_mode,
                         juce::RangedAudioParameter* fft_enablement_param)
    : path_producer_(fft_buffer)
    , path_colour_(path_colour)
    , display_mode_(display_mode)
    , fft_enablement_param_(fft_enablement_param)
{
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
MonoFftPath::resized()
{
    // Initialise the path producer.
    // We're initialising it in resized because we need to know the component's bounds,
    // which aren't known in the constructor.
    path_producer_.prepare(getLocalBounds());

    if (!isTimerRunning()) {
        startTimer(static_cast< int >(Global::FFT_PATH_PRODUCTION_FREQUENCY_MS));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
MonoFftPath::timerCallback()
{
    if (fft_enablement_param_ != nullptr && fft_enablement_param_->getValue()) {
        path_ = path_producer_.getPath();
    }
    else {
        path_.clear();
    }

    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
