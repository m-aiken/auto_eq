#include "PrimaryAnalyser.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
PrimaryAnalyser::PrimaryAnalyser(PluginProcessor& p)
{
    PluginProcessor::FftBuffers& fft_buffers = p.getFftBuffers();

    fft_path_primary_pre_eq_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::Channels::PRIMARY_LEFT),
                                                                 Theme::getColour(Theme::FFT_PRIMARY),
                                                                 Global::PATH_FILL);

    fft_path_primary_pre_eq_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::Channels::PRIMARY_RIGHT),
                                                                 Theme::getColour(Theme::FFT_PRIMARY),
                                                                 Global::PATH_FILL);

    addAndMakeVisible(db_markers_);
    addAndMakeVisible(hz_markers_);
    addAndMakeVisible(backdrop_);
    addAndMakeVisible(fft_path_primary_pre_eq_l_.get());
    addAndMakeVisible(fft_path_primary_pre_eq_r_.get());
}

/*---------------------------------------------------------------------------
**
*/
void
PrimaryAnalyser::resized()
{
    auto bounds = getLocalBounds();

    db_markers_.setBounds(juce::Rectangle< int >(0, 0, Global::ANALYSER_PADDING, bounds.getHeight()));
    hz_markers_.setBounds(juce::Rectangle< int >(Global::ANALYSER_PADDING,
                                                 0,
                                                 bounds.getWidth() - (Global::ANALYSER_PADDING * 2),
                                                 Global::ANALYSER_PADDING));

    auto padded_bounds = bounds.reduced(Global::ANALYSER_PADDING);
    backdrop_.setBounds(padded_bounds);

    fft_path_primary_pre_eq_l_->setBounds(padded_bounds);
    fft_path_primary_pre_eq_r_->setBounds(padded_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
