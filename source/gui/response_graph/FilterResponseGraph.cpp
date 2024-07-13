#include "FilterResponseGraph.h"
#include "../look_and_feel/Theme.h"
#include "../../dsp/Equalizer.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
FilterResponseGraph::FilterResponseGraph(PluginProcessor& p)
    : eq_bands_(p)
{
    PluginProcessor::FftBuffers&        fft_buffers = p.getFftBuffers();
    juce::AudioProcessorValueTreeState& apvts       = p.getApvts();

    juce::String enable_fft_primary_pre_param_id  = GuiParams::getName(GuiParams::SHOW_FFT_PRIMARY_PRE_EQ);
    juce::String enable_fft_primary_post_param_id = GuiParams::getName(GuiParams::SHOW_FFT_PRIMARY_POST_EQ);
    juce::String enable_fft_sidechain_param_id    = GuiParams::getName(GuiParams::SHOW_FFT_SIDECHAIN);

    fft_path_primary_pre_eq_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::PRIMARY_LEFT_PRE_EQ),
                                                                 Theme::FFT_PRIMARY_PRE_EQ,
                                                                 apvts.getParameter(enable_fft_primary_pre_param_id));

    fft_path_primary_pre_eq_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::PRIMARY_RIGHT_PRE_EQ),
                                                                 Theme::FFT_PRIMARY_PRE_EQ,
                                                                 apvts.getParameter(enable_fft_primary_pre_param_id));

    fft_path_primary_post_eq_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::PRIMARY_LEFT_POST_EQ),
                                                                  Theme::FFT_PRIMARY_POST_EQ,
                                                                  apvts.getParameter(enable_fft_primary_post_param_id));

    fft_path_primary_post_eq_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::PRIMARY_RIGHT_POST_EQ),
                                                                  Theme::FFT_PRIMARY_POST_EQ,
                                                                  apvts.getParameter(enable_fft_primary_post_param_id));

    fft_path_sidechain_l_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::SIDECHAIN_LEFT),
                                                            Theme::FFT_SIDECHAIN,
                                                            apvts.getParameter(enable_fft_sidechain_param_id));

    fft_path_sidechain_r_ = std::make_unique< MonoFftPath >(fft_buffers.at(Global::FFT::SIDECHAIN_RIGHT),
                                                            Theme::FFT_SIDECHAIN,
                                                            apvts.getParameter(enable_fft_sidechain_param_id));

    addAndMakeVisible(backdrop_);
    addAndMakeVisible(db_scale_);
    addAndMakeVisible(hz_scale_);
    addAndMakeVisible(eq_bands_);

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
    const uint8            padding       = Global::ANALYSER_PADDING;
    juce::Rectangle< int > y_padded_bounds(0, padding, bounds_width, bounds_height - (padding * 2));
    juce::Rectangle< int > db_scale_bounds(8, 0, padding, bounds_height);
    juce::Rectangle< int > hz_scale_bounds(0, bounds.getBottom() - padding, bounds_width, padding);

    backdrop_.setBounds(y_padded_bounds);

    db_scale_.setBounds(db_scale_bounds);
    hz_scale_.setBounds(hz_scale_bounds);

    fft_path_primary_pre_eq_l_->setBounds(y_padded_bounds);
    fft_path_primary_pre_eq_r_->setBounds(y_padded_bounds);
    fft_path_primary_post_eq_l_->setBounds(y_padded_bounds);
    fft_path_primary_post_eq_r_->setBounds(y_padded_bounds);
    fft_path_sidechain_l_->setBounds(y_padded_bounds);
    fft_path_sidechain_r_->setBounds(y_padded_bounds);

    eq_bands_.setBounds(y_padded_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
