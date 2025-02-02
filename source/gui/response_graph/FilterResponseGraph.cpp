#include "FilterResponseGraph.h"
#include "GlobalConstants.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
FilterResponseGraph::FilterResponseGraph(PluginProcessor& p)
    : eq_bands_(p)
{
    PluginProcessor::FftBuffers&              fft_buffers = p.getFftBuffers();
    const juce::AudioProcessorValueTreeState& apvts       = p.getApvts();

    const juce::String power_saving_param_id = GuiParams::getName(GuiParams::POWER_SAVING);

    fft_path_primary_post_eq_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::LEFT_POST_EQ),
                                                                  Theme::FFT,
                                                                  apvts.getParameter(power_saving_param_id));

    fft_path_primary_post_eq_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::RIGHT_POST_EQ),
                                                                  Theme::FFT,
                                                                  apvts.getParameter(power_saving_param_id));

    addAndMakeVisible(backdrop_);
    addAndMakeVisible(db_scale_);
    addAndMakeVisible(hz_scale_);
    addAndMakeVisible(eq_bands_);

    addAndMakeVisible(fft_path_primary_post_eq_l_.get());
    addAndMakeVisible(fft_path_primary_post_eq_r_.get());
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseGraph::paint(juce::Graphics& g)
{
#ifdef SHOW_DEBUG_BOUNDS
    g.setColour(juce::Colours::yellow);
    g.drawRect(getLocalBounds());
#else
    juce::ignoreUnused(g);
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseGraph::resized()
{
    const auto                   bounds        = getLocalBounds();
    const auto                   bounds_width  = bounds.getWidth();
    const auto                   bounds_height = bounds.getHeight();
    const juce::Rectangle< int > y_padded_bounds(0,
                                                 Global::GRAPH_TOP_PADDING,
                                                 bounds_width,
                                                 (bounds_height - Global::GRAPH_TOP_PADDING));

    backdrop_.setBounds(y_padded_bounds);

    db_scale_.setBounds(bounds);
    hz_scale_.setBounds(bounds);

    fft_path_primary_post_eq_l_->setBounds(y_padded_bounds);
    fft_path_primary_post_eq_r_->setBounds(y_padded_bounds);

    eq_bands_.setBounds(y_padded_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
