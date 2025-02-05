#pragma once

#include <JuceHeader.h>

#include "BandUpdater.h"

class BandParameterUpdater : public juce::Thread
{
public:
    static constexpr uint16 UPDATE_FREQUENCY_MS = 20;

public:
    BandParameterUpdater(juce::AudioProcessorValueTreeState& apvts, BandUpdater& band_updater);
    ~BandParameterUpdater() override;

    void run() override;

private:
    void updateParameters() const;

    juce::AudioProcessorValueTreeState& apvts_;
    BandUpdater&                        band_updater_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandParameterUpdater)
};
