#include "Analyser.h"

/*---------------------------------------------------------------------------
**
*/
Analyser::Analyser(PluginProcessor& p)
{
    PluginProcessor::FftBuffers& fft_buffers = p.getFftBuffers();

    spectrogram_paths_.at(Global::Channels::PRIMARY_LEFT) =
        std::make_unique< MonoSpectrogramPath >(fft_buffers.at(Global::Channels::PRIMARY_LEFT),
                                                juce::Colours::aquamarine,
                                                Global::PATH_STROKE);

    spectrogram_paths_.at(Global::Channels::PRIMARY_RIGHT) =
        std::make_unique< MonoSpectrogramPath >(fft_buffers.at(Global::Channels::PRIMARY_RIGHT),
                                                juce::Colours::red,
                                                Global::PATH_STROKE);

    spectrogram_paths_.at(Global::Channels::SIDECHAIN_LEFT) =
        std::make_unique< MonoSpectrogramPath >(fft_buffers.at(Global::Channels::SIDECHAIN_LEFT),
                                                juce::Colours::orange.withAlpha(0.2f),
                                                Global::PATH_FILL);

    spectrogram_paths_.at(Global::Channels::SIDECHAIN_RIGHT) =
        std::make_unique< MonoSpectrogramPath >(fft_buffers.at(Global::Channels::SIDECHAIN_RIGHT),
                                                juce::Colours::green.withAlpha(0.2f),
                                                Global::PATH_FILL);

    addAndMakeVisible(backdrop_);

    for (int i = 0; i < Global::Channels::NUM_INPUTS; ++i) {
        addAndMakeVisible(spectrogram_paths_.at(i).get());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
Analyser::resized()
{
    auto bounds = getLocalBounds();

    backdrop_.setBounds(bounds);

    for (int i = 0; i < Global::Channels::NUM_INPUTS; ++i) {
        spectrogram_paths_.at(i)->setBounds(bounds);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
