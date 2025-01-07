#pragma once

#include <JuceHeader.h>

#include "ButtonToolbar.h"
#include "PluginProcessor.h"
#include "SaveDialogBase.h"

class SaveAsDialog : public SaveDialogBase
{
public:
    SaveAsDialog(PluginProcessor& processor_ref, ButtonToolbar& toolbar);

    void buttonClicked(juce::Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SaveAsDialog)
};
