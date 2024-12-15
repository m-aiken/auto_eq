#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "TransportButton.h"

class TransportGroup : public juce::Component
{
public:
    explicit TransportGroup(juce::AudioProcessorValueTreeState& apvts);

    void resized() override;

    TransportButton& getButton();

private:
    DisableableLabel label_;
    TransportButton  button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportGroup)
};
