#include "PresetManager.h"
#include "GlobalConstants.h"

/*static*/ const juce::Identifier PresetManager::NODE_IDENTIFIER_PRESETS  = "presets";
/*static*/ const juce::Identifier PresetManager::NODE_IDENTIFIER_PRESET   = "preset";
/*static*/ const juce::Identifier PresetManager::NODE_IDENTIFIER_BAND     = "band";
/*static*/ const juce::Identifier PresetManager::PROPERTY_IDENTIFIER_NAME = "name";
/*static*/ const juce::Identifier PresetManager::PROPERTY_IDENTIFIER_ID   = "id";
/*static*/ const juce::Identifier PresetManager::PROPERTY_IDENTIFIER_GAIN = "gain";
/*static*/ const juce::String     PresetManager::DEFAULT_PRESET_NAME      = "unsaved preset...";

/*---------------------------------------------------------------------------
**
*/
PresetManager::PresetManager(const juce::AudioProcessorValueTreeState& apvts)
    : apvts_(apvts)
    , presets_(NODE_IDENTIFIER_PRESETS)
    , currently_loaded_preset_name_(DEFAULT_PRESET_NAME)
{
    undo_manager_ = std::make_unique< juce::UndoManager >();

    // Add the default empty preset.
    presets_.addChild(getDefaultPreset(undo_manager_.get()), DEFAULT_PRESET_INDEX, undo_manager_.get());

#ifdef ADD_TEST_PRESETS
    addTestPreset("John Doe", 1.0, undo_manager_.get());
    addTestPreset("Steve Poe", 2.0, undo_manager_.get());
    addTestPreset("Jane Goe", 3.0, undo_manager_.get());
    addTestPreset("Will Boe", 4.0, undo_manager_.get());
    addTestPreset("Sarah Hoe", 5.0, undo_manager_.get());
#endif
}

/*---------------------------------------------------------------------------
**
*/
void
PresetManager::savePreset() const
{
    juce::ValueTree preset = getCurrentlyLoadedPreset();

    if (isValidPreset(preset)) {
        writeCurrentApvtsBandSettingsToPreset(preset);
    }
}

/*---------------------------------------------------------------------------
**
*/
int
PresetManager::savePresetAs(const juce::String& new_name)
{
    int index = INVALID_PRESET_INDEX;

    if (new_name.isEmpty()) {
        // Can't save without a name.
        return index;
    }

    if (new_name == getCurrentlyLoadedPresetName() && !currentPresetHasDefaultName()) {
        // The user has decided to keep the existing name.
        // This is valid as long as it is a user defined name.
        // Process as a standard "Save" operation.
        savePreset();

        index = getCurrentlyLoadedPresetIndex();
    }
    else if (hasPresetWithName(new_name)) {
        // The user wants to overwrite an existing preset (they've been warned!).
        // This is valid.
        juce::ValueTree existing_preset = getPreset(new_name);

        writeCurrentApvtsBandSettingsToPreset(existing_preset);

        index = getPresetIndex(existing_preset);
    }
    else {
        // The user has provided a new name for the preset.
        // We want to add a new entry to our presets state.
        juce::ValueTree preset = getDefaultPreset(undo_manager_.get());

        if (isValidPreset(preset)) {
            setPresetName(preset, new_name);
            writeCurrentApvtsBandSettingsToPreset(preset);

            index = presets_.getNumChildren();

            presets_.addChild(preset, index, undo_manager_.get());
        }
    }

    return index;
}

/*---------------------------------------------------------------------------
**
*/
const juce::ValueTree&
PresetManager::getPresets() const
{
    return presets_;
}

/*---------------------------------------------------------------------------
**
*/
juce::ValueTree
PresetManager::getPreset(const int preset_index) const
{
    juce::ValueTree ret;

    if (presets_.isValid() && presets_.hasType(NODE_IDENTIFIER_PRESETS) && (presets_.getNumChildren() > preset_index)) {
        ret = presets_.getChild(preset_index);
    }

    return ret;
}

/*---------------------------------------------------------------------------
**
*/
juce::ValueTree
PresetManager::getPreset(const juce::String& preset_name) const
{
    const juce::ValueTree& preset = presets_.getChildWithProperty(PROPERTY_IDENTIFIER_NAME, preset_name);

    return preset.isValid() ? preset : juce::ValueTree();
}

/*---------------------------------------------------------------------------
**
*/
bool
PresetManager::hasPresetWithName(const juce::String& preset_name) const
{
    if (presets_.isValid() && presets_.hasType(NODE_IDENTIFIER_PRESETS)) {
        const juce::ValueTree preset = presets_.getChildWithProperty(PROPERTY_IDENTIFIER_NAME, preset_name);

        return isValidPreset(preset);
    }

    return false;
}

/*---------------------------------------------------------------------------
**
*/
int
PresetManager::getNumPresets() const
{
    const juce::ValueTree& presets = getPresets();

    if (presets.hasType(NODE_IDENTIFIER_PRESETS) && presets.isValid()) {
        return presets.getNumChildren();
    }

    return 0;
}

/*---------------------------------------------------------------------------
**
*/
bool
PresetManager::isValidPreset(const juce::ValueTree& preset)
{
    bool ok = true;

    ok &= preset.isValid();
    ok &= preset.hasType(NODE_IDENTIFIER_PRESET);
    ok &= preset.getNumChildren() == Equalizer::NUM_BANDS;

    return ok;
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::String
PresetManager::getPresetName(const juce::ValueTree& preset)
{
    const bool ok = preset.hasType(NODE_IDENTIFIER_PRESET) && preset.isValid()
                    && preset.hasProperty(PROPERTY_IDENTIFIER_NAME);

    return ok ? preset.getProperty(PROPERTY_IDENTIFIER_NAME).toString() : DEFAULT_PRESET_NAME;
}

/*---------------------------------------------------------------------------
**
*/
int
PresetManager::getPresetIndex(const juce::ValueTree& preset) const
{
    if (presets_.hasType(NODE_IDENTIFIER_PRESETS) && presets_.isValid()) {
        const juce::String& name = getPresetName(preset);

        for (int i = 0; i < getNumPresets(); ++i) {
            const juce::ValueTree& candidate = presets_.getChild(i);

            if (isValidPreset(candidate) && getPresetName(candidate) == name) {
                return i;
            }
        }
    }

    return INVALID_PRESET_INDEX;
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ double
PresetManager::getPresetBandGain(const juce::ValueTree& preset, const Equalizer::BAND_ID band_id)
{
    double ret = 0.0;

    if (isValidPreset(preset)) {
        const juce::ValueTree& band = preset.getChildWithProperty(PROPERTY_IDENTIFIER_ID, band_id);

        if (band.isValid() && band.hasType(NODE_IDENTIFIER_BAND) && band.hasProperty(PROPERTY_IDENTIFIER_GAIN)) {
            ret = band.getProperty(PROPERTY_IDENTIFIER_GAIN);
        }
    }

    return ret;
}

/*---------------------------------------------------------------------------
**
*/
double
PresetManager::getPresetBandGain(const juce::String& preset_name, const Equalizer::BAND_ID band_id) const
{
    return getPresetBandGain(getPreset(preset_name), band_id);
}

/*---------------------------------------------------------------------------
**
*/
juce::ValueTree
PresetManager::getCurrentlyLoadedPreset() const
{
    return getPreset(getCurrentlyLoadedPresetName());
}

/*---------------------------------------------------------------------------
**
*/
int
PresetManager::getCurrentlyLoadedPresetIndex() const
{
    return getPresetIndex(getCurrentlyLoadedPreset());
}

/*---------------------------------------------------------------------------
**
*/
juce::String
PresetManager::getCurrentlyLoadedPresetName() const
{
    return currently_loaded_preset_name_;
}

/*---------------------------------------------------------------------------
**
*/
void
PresetManager::setCurrentlyLoadedPresetName(const juce::String& preset_name)
{
    if (hasPresetWithName(preset_name)) {
        currently_loaded_preset_name_ = preset_name;
    }
}

/*---------------------------------------------------------------------------
**
*/
bool
PresetManager::currentPresetIsUnchangedDefault() const
{
    return (currentPresetHasDefaultName() && !currentPresetHasUnsavedChanges());
}

/*---------------------------------------------------------------------------
**
*/
bool
PresetManager::currentPresetHasDefaultName() const
{
    return (getCurrentlyLoadedPresetName() == DEFAULT_PRESET_NAME);
}

/*---------------------------------------------------------------------------
**
*/
bool
PresetManager::currentPresetHasUnsavedChanges() const
{
    // The bands as represented in the AudioProcessorValueTreeState have the current value.
    // If any of those band values differ from our preset juce::ValueTree, the preset has
    // unsaved changes.
    const juce::String& preset_name = getCurrentlyLoadedPresetName();

    for (int i = 0; i < Equalizer::NUM_BANDS; ++i) {
        const auto                        band_id      = static_cast< Equalizer::BAND_ID >(i);
        const juce::String                parameter_id = Equalizer::getBandName(band_id);
        const juce::RangedAudioParameter* apvts_param  = apvts_.getParameter(parameter_id);

        if (apvts_param == nullptr) {
            continue;
        }

        const float apvts_band_gain = apvts_param->convertFrom0to1(apvts_param->getValue());

        if (getPresetBandGain(preset_name, band_id) != apvts_band_gain) {
            // Unsaved change.
            return true;
        }
    }

    return false;
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::ValueTree
PresetManager::getDefaultPreset(juce::UndoManager* um)
{
    /*
    The default construction for an EQ Preset looks like this:

    (ValueTree)
    { "preset", {{ "name", "unsaved preset..." }},
      {
        { "band", {{ "id", 0 }, { "gain", 0.0 }}},
        { "band", {{ "id", 1 }, { "gain", 0.0 }}},
        etc...
        { "band", {{ "id", 30 }, { "gain", 0.0 }}},
      }
    }

    (XML)
    <preset name="unsaved preset...">
      <band id="0" gain="0.0"/>
      <band id="1" gain="0.0"/>
      etc...
      <band id="30" gain="0.0"/>
    </preset>
    */

    juce::ValueTree preset(NODE_IDENTIFIER_PRESET);

    preset.setProperty(PROPERTY_IDENTIFIER_NAME, DEFAULT_PRESET_NAME, um);

    for (int i = 0; i < Equalizer::NUM_BANDS; ++i) {
        juce::ValueTree band(NODE_IDENTIFIER_BAND);

        band.setProperty(PROPERTY_IDENTIFIER_ID, i, um);
        band.setProperty(PROPERTY_IDENTIFIER_GAIN, Equalizer::DEFAULT_BAND_DB, um);

        preset.addChild(band, -1, um);
    }

    return preset;
}

/*---------------------------------------------------------------------------
**
*/
void
PresetManager::addTestPreset(const juce::String& preset_name, const double band_gain, juce::UndoManager* um)
{
    juce::ValueTree preset(NODE_IDENTIFIER_PRESET);

    preset.setProperty(PROPERTY_IDENTIFIER_NAME, preset_name, um);

    for (int i = 0; i < Equalizer::NUM_BANDS; ++i) {
        juce::ValueTree band(NODE_IDENTIFIER_BAND);

        band.setProperty(PROPERTY_IDENTIFIER_ID, i, um);
        band.setProperty(PROPERTY_IDENTIFIER_GAIN, band_gain, um);

        preset.addChild(band, -1, um);
    }

    presets_.addChild(preset, presets_.getNumChildren(), um);
}

/*---------------------------------------------------------------------------
**
*/
void
PresetManager::writeCurrentApvtsBandSettingsToPreset(juce::ValueTree& preset) const
{
    if (!isValidPreset(preset)) {
        return;
    }

    for (uint8 i = 0; i < Equalizer::NUM_BANDS; ++i) {
        const auto                        band_id      = static_cast< Equalizer::BAND_ID >(i);
        const juce::String                parameter_id = Equalizer::getBandName(band_id);
        const juce::RangedAudioParameter* apvts_param  = apvts_.getParameter(parameter_id);

        if (apvts_param == nullptr) {
            continue;
        }

        const float db_value = apvts_param->convertFrom0to1(apvts_param->getValue());

        setPresetBandGain(preset, band_id, db_value);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PresetManager::setPresetName(juce::ValueTree& preset, const juce::String& name) const
{
    if (preset.hasType(NODE_IDENTIFIER_PRESET) && preset.isValid() && preset.hasProperty(PROPERTY_IDENTIFIER_NAME)) {
        preset.setProperty(PROPERTY_IDENTIFIER_NAME, name, undo_manager_.get());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PresetManager::setPresetBandGain(const juce::ValueTree& preset, const Equalizer::BAND_ID band_id, const double gain) const
{
    if (!preset.hasType(NODE_IDENTIFIER_PRESET) || !preset.isValid()) {
        return;
    }

    // Note the function is const and we're grabbing the band ValueTree to update by copy.
    // juce::ValueTree's are just references to a shared underlying container.
    // (Good news! because this helps us avoid the non-const l-value reference headache).
    juce::ValueTree band = preset.getChildWithProperty(PROPERTY_IDENTIFIER_ID, band_id);

    if (band.hasType(NODE_IDENTIFIER_BAND) && band.isValid()) {
        band.setProperty(PROPERTY_IDENTIFIER_GAIN, gain, undo_manager_.get());
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
