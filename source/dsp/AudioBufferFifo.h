#pragma once

#include <JuceHeader.h>

class AudioBufferFifo
{
public:
    AudioBufferFifo();

    void               prepare(const juce::dsp::ProcessSpec& process_spec);
    [[nodiscard]] bool isPrepared() const;

    void                                     push(juce::AudioBuffer< float > buffer);
    [[nodiscard]] juce::AudioBuffer< float > pull() const;

private:
    static constexpr size_t                             FIFO_SIZE = 24;
    std::array< juce::AudioBuffer< float >, FIFO_SIZE > fifo_;
    size_t                                              fifo_write_idx_;
    size_t                                              fifo_read_idx_;

    bool is_prepared_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioBufferFifo)
};
