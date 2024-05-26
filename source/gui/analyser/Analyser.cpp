#include "Analyser.h"

/*---------------------------------------------------------------------------
**
*/
Analyser::Analyser(PluginProcessor& p)
{
    addAndMakeVisible(backdrop_);

    path_colours_.at(Global::PLAYBACK_LEFT)  = juce::Colours::aquamarine;
    path_colours_.at(Global::PLAYBACK_RIGHT) = juce::Colours::red;
    path_colours_.at(Global::AMBIENT_LEFT)   = juce::Colours::green;
    path_colours_.at(Global::AMBIENT_RIGHT)  = juce::Colours::yellow;

    PluginProcessor::FftBuffers& fft_buffers = p.getFftBuffers();

    for (int i = 0; i < Global::NUM_INPUTS; ++i) {
        spectrogram_paths_.at(i) = std::make_unique< MonoSpectrogramPath >(fft_buffers.at(i), path_colours_.at(i));
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

    for (int i = 0; i < Global::NUM_INPUTS; ++i) {
        spectrogram_paths_.at(i)->setBounds(bounds);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
