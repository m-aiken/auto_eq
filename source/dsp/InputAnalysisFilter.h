#pragma once

#include <JuceHeader.h>

#include "AudioBufferFifo.h"
#include "Equalizer.h"

class InputAnalysisFilter : public juce::Thread
{
public:
    static constexpr uint16 ANALYSIS_FREQUENCY_MS = 200;  //! How frequently the analysis is performed (in milliseconds).

public:
    InputAnalysisFilter();
    ~InputAnalysisFilter() override;

    void run() override;

    void prepare(const juce::dsp::ProcessSpec& process_spec);
    bool isPrepared() const;

    void  pushBufferForAnalysis(const juce::AudioBuffer< float >& buffer);
    float getBandDbAdjustment(const Equalizer::BAND_ID band_id) const;

private:
    using Filter = juce::dsp::LinkwitzRileyFilter< float >;
    typedef std::array< Filter, Equalizer::NUM_BANDS >                   SingleBandFilterSequence;
    typedef std::array< SingleBandFilterSequence, Equalizer::NUM_BANDS > FilterMatrix;

    void  initFilters();
    void  processInputBuffer();
    float getBandInputDb(const Equalizer::BAND_ID band_id) const;
    void  printBandMagnitudesPreProcessing() const;

    FilterMatrix                                                   filter_matrix_;
    std::array< juce::AudioBuffer< float >, Equalizer::NUM_BANDS > band_buffers_;
    std::array< float, Equalizer::NUM_BANDS >                      band_adjustments_;

    // Audio buffer FIFO.
    // The audio thread pushes buffers into this FIFO (by copy).
    // On the timer callback we grab one of the buffers and perform the analysis.
    // This prevents blocking the audio thread and gives better control over the
    // frequency of the analysis.
    AudioBufferFifo fifo_;

    bool is_prepared_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputAnalysisFilter)
};
