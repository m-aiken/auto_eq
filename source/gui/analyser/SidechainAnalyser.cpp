#include "SidechainAnalyser.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
SidechainAnalyser::SidechainAnalyser(PluginProcessor& p)
{
    PluginProcessor::FftBuffers& fft_buffers = p.getFftBuffers();

    fft_path_sidechain_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::SIDECHAIN_LEFT),
                                                            Theme::getColour(Theme::FFT_SIDECHAIN),
                                                            Global::PATH_FILL);

    fft_path_sidechain_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::SIDECHAIN_RIGHT),
                                                            Theme::getColour(Theme::FFT_SIDECHAIN),
                                                            Global::PATH_FILL);

    addAndMakeVisible(db_markers_);
    addAndMakeVisible(hz_markers_);
    addAndMakeVisible(backdrop_);
    addAndMakeVisible(fft_path_sidechain_l_.get());
    addAndMakeVisible(fft_path_sidechain_r_.get());
}

/*---------------------------------------------------------------------------
**
*/
void
SidechainAnalyser::resized()
{
    auto bounds = getLocalBounds();

    db_markers_.setBounds(juce::Rectangle< int >(0, 0, Global::ANALYSER_PADDING, bounds.getHeight()));
    hz_markers_.setBounds(juce::Rectangle< int >(Global::ANALYSER_PADDING,
                                                 0,
                                                 bounds.getWidth() - (Global::ANALYSER_PADDING * 2),
                                                 Global::ANALYSER_PADDING));

    auto padded_bounds = bounds.reduced(Global::ANALYSER_PADDING);
    backdrop_.setBounds(padded_bounds);

    fft_path_sidechain_l_->setBounds(padded_bounds);
    fft_path_sidechain_r_->setBounds(padded_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
