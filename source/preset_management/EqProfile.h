#pragma once

#include <JuceHeader.h>

#include "Equalizer.h"

class EqProfile
{
public:
    EqProfile();

    [[nodiscard]] juce::String getName() const;
    void                       setName(const juce::String& profile_name);

    [[nodiscard]] double getBandGain(const Equalizer::BAND_ID band_id) const;
    void                 setBandGain(const Equalizer::BAND_ID band_id, const double gain) const;

private:
    static const juce::String    XML_TAG_PROFILE;
    static const juce::String    XML_ATTR_PROFILE_NAME;
    static const juce::String    XML_TAG_BAND;
    static const juce::String    XML_ATTR_BAND_ID;
    static const juce::String    XML_ATTR_BAND_GAIN;
    static const juce::ValueTree INITIAL_DATA;

private:
    void initialiseProfile();

    juce::ValueTree                      data_;
    std::unique_ptr< juce::UndoManager > undo_manager_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqProfile)
};
