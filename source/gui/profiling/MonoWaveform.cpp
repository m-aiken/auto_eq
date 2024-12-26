#include "GlobalConstants.h"
#include "MonoWaveform.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
MonoWaveform::MonoWaveform()
    : juce::AudioVisualiserComponent(1)
    , theme_tracker_(Theme::app_is_in_dark_mode)
{
    setColours(Theme::getColour(Theme::MAIN_BG), Theme::getColour(Theme::TEXT));
}

/*---------------------------------------------------------------------------
**
*/
void
MonoWaveform::paint(juce::Graphics& g)
{
    // This is a workaround to handle dark/light theme changes.
    // If the theme has changed reset the waveform colours.
    // It looks strange to keep setting the "same" colours, but the actual colour
    // Theme::getColour returns is different depending on the mode (light or dark).
    // I.e. Theme::TEXT refers to one colour in light mode and another in dark mode.
    if (Theme::app_is_in_dark_mode != theme_tracker_) {
        setColours(Theme::getColour(Theme::MAIN_BG), Theme::getColour(Theme::TEXT));

        theme_tracker_ = Theme::app_is_in_dark_mode;
    }

    // Then just call the existing paint method.
    // We don't want to have to redefine the entire painting logic for the waveform.
    juce::AudioVisualiserComponent::paint(g);

    // Draw an invisible border (same as the background colour) to hide the artefacts that can occur at the edges.
    g.setColour(Theme::getColour(Theme::MAIN_BG));
    g.drawRect(getLocalBounds(), 6);

#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::green);
    g.drawRect(getLocalBounds());
#endif
}

/*---------------------------------------------------------------------------
** End of File
*/
