#pragma once

#include <JuceHeader.h>

#include "Equalizer.h"

class PresetManager
{
public:
    // There's always a default (empty) preset in our preset state at index zero.
    // This preset isn't added to the "Load" menu, so it's essentially invisible.
    // When the user clicks "New" what actually happens is this hidden default preset is loaded.
    // When the default preset is loaded the user cannot "Save", they can only "Save As",
    // which in turn saves the current preset's state as a new preset.
    static constexpr int DEFAULT_PRESET_INDEX            = 0;
    static constexpr int FIRST_USER_DEFINED_PRESET_INDEX = 1;
    static constexpr int INVALID_PRESET_INDEX            = -1;

    static const juce::Identifier NODE_IDENTIFIER_PRESETS;
    static const juce::Identifier NODE_IDENTIFIER_PRESET;
    static const juce::Identifier NODE_IDENTIFIER_BAND;
    static const juce::Identifier PROPERTY_IDENTIFIER_NAME;
    static const juce::Identifier PROPERTY_IDENTIFIER_ID;
    static const juce::Identifier PROPERTY_IDENTIFIER_GAIN;
    static const juce::String     DEFAULT_PRESET_NAME;

public:
    explicit PresetManager(const juce::AudioProcessorValueTreeState& apvts);

    void savePreset() const;
    int  savePresetAs(const juce::String& new_name);

    [[nodiscard]] const juce::ValueTree& getPresets() const;
    [[nodiscard]] juce::ValueTree        getPreset(const int preset_index) const;
    [[nodiscard]] juce::ValueTree        getPreset(const juce::String& preset_name) const;
    [[nodiscard]] bool                   hasPresetWithName(const juce::String& preset_name) const;
    [[nodiscard]] int                    getNumPresets() const;
    static bool                          isValidPreset(const juce::ValueTree& preset);

    static juce::String  getPresetName(const juce::ValueTree& preset);
    int                  getPresetIndex(const juce::ValueTree& preset) const;
    static double        getPresetBandGain(const juce::ValueTree& preset, const Equalizer::BAND_ID band_id);
    [[nodiscard]] double getPresetBandGain(const juce::String& preset_name, const Equalizer::BAND_ID band_id) const;

    [[nodiscard]] juce::ValueTree getCurrentlyLoadedPreset() const;
    [[nodiscard]] int             getCurrentlyLoadedPresetIndex() const;
    [[nodiscard]] juce::String    getCurrentlyLoadedPresetName() const;
    void                          setCurrentlyLoadedPresetName(const juce::String& preset_name);

    [[nodiscard]] bool currentPresetIsUnchangedDefault() const;
    [[nodiscard]] bool currentPresetHasDefaultName() const;
    [[nodiscard]] bool currentPresetHasUnsavedChanges() const;

private:
    [[nodiscard]] static juce::ValueTree getDefaultPreset(juce::UndoManager* um);

    void addTestPreset(const juce::String& preset_name, const double band_gain, juce::UndoManager* um);

    void writeCurrentApvtsBandSettingsToPreset(juce::ValueTree& preset) const;

    void setPresetName(juce::ValueTree& preset, const juce::String& name) const;
    void setPresetBandGain(const juce::ValueTree& preset, const Equalizer::BAND_ID band_id, const double gain) const;

private:
    const juce::AudioProcessorValueTreeState& apvts_;
    juce::ValueTree                           presets_;
    std::unique_ptr< juce::UndoManager >      undo_manager_;
    juce::String                              currently_loaded_preset_name_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetManager)
};
