#include "FilterResponseGraph.h"
#include "../Theme.h"
#include "../../dsp/FilterFactory.h"
#include "../../utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
FilterResponseGraph::FilterResponseGraph(PluginProcessor& p)
    : db_scale_(FilterFactory::MAX_BAND_DB_CUT, FilterFactory::MAX_BAND_DB_BOOST, 6)
    , response_curve_(p)
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

    addAndMakeVisible(backdrop_);
    addAndMakeVisible(db_scale_);
    addAndMakeVisible(hz_scale_);
    addAndMakeVisible(response_curve_);

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
    if (Global::SHOW_DEBUG_BOUNDS) {
        g.setColour(juce::Colours::yellow);
        g.drawRect(getLocalBounds());
    }
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
    response_curve_.setBounds(y_padded_bounds);
    db_scale_.setBounds(db_scale_bounds);
    hz_scale_.setBounds(hz_scale_bounds);

    fft_path_primary_pre_eq_l_->setBounds(y_padded_bounds);
    fft_path_primary_pre_eq_r_->setBounds(y_padded_bounds);
    fft_path_primary_post_eq_l_->setBounds(y_padded_bounds);
    fft_path_primary_post_eq_r_->setBounds(y_padded_bounds);
    fft_path_sidechain_l_->setBounds(y_padded_bounds);
    fft_path_sidechain_r_->setBounds(y_padded_bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
