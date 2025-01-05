#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "GlobalConstants.h"

class MeterLabelGroup : public juce::Component
{
public:
    MeterLabelGroup();

    void resized() override;

private:
    std::array< std::unique_ptr< DisableableLabel >, Global::Meters::NUM_METERS > labels_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterLabelGroup)
};
