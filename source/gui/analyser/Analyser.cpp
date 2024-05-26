#include "Analyser.h"

/*---------------------------------------------------------------------------
**
*/
Analyser::Analyser(PluginProcessor& p)
    : spectrogram_path_(p.getFftBufferPlaybackSourceL())
{
    addAndMakeVisible(backdrop_);
    addAndMakeVisible(spectrogram_path_);
}

/*---------------------------------------------------------------------------
**
*/
void
Analyser::resized()
{
    auto bounds = getLocalBounds();

    backdrop_.setBounds(bounds);
    spectrogram_path_.setBounds(bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
