#pragma once

#include <JuceHeader.h>

#include "Equalizer.h"

class InputAnalysisFilter : public juce::Thread
{
    using Filter = juce::dsp::LinkwitzRileyFilter< float >;

public:
    InputAnalysisFilter(const juce::AudioProcessorValueTreeState& apvts);
    ~InputAnalysisFilter();

    void run() override;

    void prepare(juce::dsp::ProcessSpec& process_spec);
    void pushBufferForAnalysis(juce::AudioBuffer< float > buffer);

private:
    void                       initFilters();
    void                       processInputBuffer();
    void                       updateBandValues();
    float                      getBandInputDb(Equalizer::BAND_ID band_id) const;
    float                      getBandDbAdjustment(Equalizer::BAND_ID band_id) const;
    juce::AudioParameterFloat* getBandParameter(Equalizer::BAND_ID band_id);

    // Debug functions.
    void printBandMagnitudesPreProcessing();
    void printBandAdjustments();

    static const uint16 ANALYSIS_FREQUENCY_MS;  //! How frequently the analysis is performed (in milliseconds).

    typedef std::array< Filter, Equalizer::NUM_BANDS >                   SingleBandFilterSequence;
    typedef std::array< SingleBandFilterSequence, Equalizer::NUM_BANDS > FilterMatrix;

    FilterMatrix                                                   filter_matrix_;
    std::array< juce::AudioBuffer< float >, Equalizer::NUM_BANDS > band_buffers_;
    std::array< float, Equalizer::NUM_BANDS >                      band_adjustments_;

    // Audio buffer FIFO.
    // The audio thread pushes buffers into this FIFO (by copy).
    // On the timer callback we grab one of the buffers and perform the analysis.
    // This prevents blocking the audio thread and gives better control over the
    // frequency of the analysis.
    static constexpr size_t                             FIFO_SIZE = 24;
    std::array< juce::AudioBuffer< float >, FIFO_SIZE > fifo_;
    size_t                                              fifo_write_idx_;
    size_t                                              fifo_read_idx_;

    const juce::AudioProcessorValueTreeState& apvts_;

    bool is_prepared_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputAnalysisFilter)
};
