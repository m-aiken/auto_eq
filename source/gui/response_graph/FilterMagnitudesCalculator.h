#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class FilterMagnitudesCalculator : juce::Thread
{
public:
    typedef std::vector< double > MagnitudesVector;

public:
    explicit FilterMagnitudesCalculator(PluginProcessor& processor_ref);
    ~FilterMagnitudesCalculator() override;

    void prepare(int num_x_pixels);

    void run() override;

    MagnitudesVector& getMagnitudes();

private:
    void resetMagnitudesVectors();
    void resetMagnitudesVector(size_t index);
    void calculateMagnitudes();

private:
    static constexpr size_t                   FIFO_SIZE = 8;
    std::array< MagnitudesVector, FIFO_SIZE > fifo_;
    size_t                                    fifo_write_idx_;
    size_t                                    fifo_read_idx_;

    PluginProcessor& processor_ref_;
    int              num_x_pixels_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterMagnitudesCalculator)
};
