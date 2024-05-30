#include "Analyser.h"
#include "../Theme.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
Analyser::Analyser(PluginProcessor& p)
{
    PluginProcessor::FftBuffers& fft_buffers = p.getFftBuffers();

    fft_paths_.at(
        Global::Channels::PRIMARY_LEFT) = std::make_unique< MonoFftPath >(fft_buffers.at(Global::Channels::PRIMARY_LEFT),
                                                                          Theme::getColour(Theme::FFT_PRIMARY),
                                                                          Global::PATH_FILL);

    fft_paths_.at(
        Global::Channels::PRIMARY_RIGHT) = std::make_unique< MonoFftPath >(fft_buffers.at(Global::Channels::PRIMARY_RIGHT),
                                                                           Theme::getColour(Theme::FFT_PRIMARY),
                                                                           Global::PATH_FILL);

    fft_paths_.at(Global::Channels::SIDECHAIN_LEFT) =
        std::make_unique< MonoFftPath >(fft_buffers.at(Global::Channels::SIDECHAIN_LEFT),
                                        Theme::getColour(Theme::FFT_SIDECHAIN).withAlpha(0.2f),
                                        Global::PATH_FILL);

    fft_paths_.at(Global::Channels::SIDECHAIN_RIGHT) =
        std::make_unique< MonoFftPath >(fft_buffers.at(Global::Channels::SIDECHAIN_RIGHT),
                                        Theme::getColour(Theme::FFT_SIDECHAIN).withAlpha(0.2f),
                                        Global::PATH_FILL);

    addAndMakeVisible(db_markers_);
    addAndMakeVisible(hz_markers_);
    addAndMakeVisible(backdrop_);

    for (int i = 0; i < Global::Channels::NUM_INPUTS; ++i) {
        addAndMakeVisible(fft_paths_.at(i).get());
    }
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

    for (int i = 0; i < Global::Channels::NUM_INPUTS; ++i) {
        fft_paths_.at(i)->setBounds(padded_bounds);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
