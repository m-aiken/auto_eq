#include "Analyser.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
Analyser::Analyser(PluginProcessor& p)
    : db_markers_(Global::NEG_INF, Global::MAX_DB, 6)
{
    PluginProcessor::FftBuffers& fft_buffers = p.getFftBuffers();

    fft_path_primary_pre_eq_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::PRIMARY_LEFT_PRE_EQ),
                                                                 Theme::FFT_PRIMARY_PRE_EQ,
                                                                 Global::PATH_FILL);

    fft_path_primary_pre_eq_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::PRIMARY_RIGHT_PRE_EQ),
                                                                 Theme::FFT_PRIMARY_PRE_EQ,
                                                                 Global::PATH_FILL);

    fft_path_primary_post_eq_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::PRIMARY_LEFT_POST_EQ),
                                                                  Theme::FFT_PRIMARY_POST_EQ,
                                                                  Global::PATH_STROKE);

    fft_path_primary_post_eq_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::PRIMARY_RIGHT_POST_EQ),
                                                                  Theme::FFT_PRIMARY_POST_EQ,
                                                                  Global::PATH_STROKE);

    fft_path_sidechain_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::SIDECHAIN_LEFT),
                                                            Theme::FFT_SIDECHAIN,
                                                            Global::PATH_FILL);

    fft_path_sidechain_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::SIDECHAIN_RIGHT),
                                                            Theme::FFT_SIDECHAIN,
                                                            Global::PATH_FILL);

    addAndMakeVisible(db_markers_);
    addAndMakeVisible(hz_markers_);
    addAndMakeVisible(backdrop_);
    addAndMakeVisible(fft_path_primary_pre_eq_l_.get());
    addAndMakeVisible(fft_path_primary_pre_eq_r_.get());
    addAndMakeVisible(fft_path_primary_post_eq_l_.get());
    addAndMakeVisible(fft_path_primary_post_eq_r_.get());
    addAndMakeVisible(fft_path_sidechain_l_.get());
    addAndMakeVisible(fft_path_sidechain_r_.get());
}

/*---------------------------------------------------------------------------
**
*/
void
Analyser::resized()
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
    fft_path_primary_post_eq_l_->setBounds(padded_bounds);
    fft_path_primary_post_eq_r_->setBounds(padded_bounds);
    fft_path_sidechain_l_->setBounds(padded_bounds);
    fft_path_sidechain_r_->setBounds(padded_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
