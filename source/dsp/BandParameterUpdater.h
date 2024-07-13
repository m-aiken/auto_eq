#pragma once

#include <JuceHeader.h>

#include "BandUpdater.h"

class BandParameterUpdater : public juce::Thread
{
public:
    static const uint16 UPDATE_FREQUENCY_MS;

public:
    BandParameterUpdater(juce::AudioProcessorValueTreeState& apvts, BandUpdater& band_updater);
    ~BandParameterUpdater();

    void run() override;

private:
    void updateParameters();

    juce::AudioProcessorValueTreeState& apvts_;
    BandUpdater&                        band_updater_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandParameterUpdater)
};
