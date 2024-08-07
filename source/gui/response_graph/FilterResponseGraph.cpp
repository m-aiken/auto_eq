#include "FilterResponseGraph.h"
#include "GlobalConstants.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
FilterResponseGraph::FilterResponseGraph(PluginProcessor& p)
    : eq_bands_(p)
{
    PluginProcessor::FftBuffers&        fft_buffers = p.getFftBuffers();
    juce::AudioProcessorValueTreeState& apvts       = p.getApvts();

    juce::String enable_fft_primary_post_param_id = GuiParams::getName(GuiParams::SHOW_FFT);

    fft_path_primary_post_eq_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::LEFT_POST_EQ),
                                                                  Theme::FFT,
                                                                  apvts.getParameter(enable_fft_primary_post_param_id));

    fft_path_primary_post_eq_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::RIGHT_POST_EQ),
                                                                  Theme::FFT,
                                                                  apvts.getParameter(enable_fft_primary_post_param_id));

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
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
FilterResponseGraph::resized()
{
    auto                   bounds        = getLocalBounds();
    auto                   bounds_width  = bounds.getWidth();
    auto                   bounds_height = bounds.getHeight();
    juce::Rectangle< int > y_padded_bounds(0,
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
