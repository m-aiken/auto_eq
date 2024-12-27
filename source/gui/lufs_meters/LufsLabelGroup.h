#pragma once

#include <JuceHeader.h>

#include "DisableableLabel.h"
#include "GlobalConstants.h"

class LufsLabelGroup : public juce::Component
{
public:
    LufsLabelGroup();

    void resized() override;

private:
    std::array< std::unique_ptr< DisableableLabel >, Global::Meters::NUM_LOUDNESS_METERS > labels_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LufsLabelGroup)
};
