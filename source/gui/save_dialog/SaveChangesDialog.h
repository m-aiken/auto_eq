#pragma once

#include <JuceHeader.h>

#include "ButtonToolbar.h"
#include "PluginProcessor.h"
#include "SaveDialogBase.h"

class SaveChangesDialog : public SaveDialogBase
{
public:
    SaveChangesDialog(PluginProcessor& processor_ref, ButtonToolbar& toolbar);

    void buttonClicked(juce::Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SaveChangesDialog)
};
