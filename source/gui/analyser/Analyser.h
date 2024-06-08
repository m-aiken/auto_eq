#pragma once

#include <JuceHeader.h>

#include "../response_graph/MonoFftPath.h"
#include "../../PluginProcessor.h"

class Analyser : public juce::Component
{
public:
    Analyser(PluginProcessor& p);

    void resized() override;

private:
    std::unique_ptr< MonoFftPath > fft_path_primary_pre_eq_l_;
    std::unique_ptr< MonoFftPath > fft_path_primary_pre_eq_r_;
    std::unique_ptr< MonoFftPath > fft_path_primary_post_eq_l_;
    std::unique_ptr< MonoFftPath > fft_path_primary_post_eq_r_;
    std::unique_ptr< MonoFftPath > fft_path_sidechain_l_;
    std::unique_ptr< MonoFftPath > fft_path_sidechain_r_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Analyser)
};
