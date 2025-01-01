#include "EqProfile.h"

/*static*/ const juce::String XML_TAG_PROFILE       = "profile";
/*static*/ const juce::String XML_ATTR_PROFILE_NAME = "name";
/*static*/ const juce::String XML_TAG_BAND          = "band";
/*static*/ const juce::String XML_ATTR_BAND_ID      = "id";
/*static*/ const juce::String XML_ATTR_BAND_GAIN    = "gain";

/*---------------------------------------------------------------------------
**
*/
EqProfile::EqProfile()
{
    undo_manager_ = std::make_unique< juce::UndoManager >();

    initialiseProfile();
}

/*---------------------------------------------------------------------------
**
*/
juce::String
EqProfile::getName() const
{
    const bool ok = (data_.isValid() && data_.hasProperty(XML_ATTR_PROFILE_NAME));

    return ok ? data_.getProperty(XML_ATTR_PROFILE_NAME).toString() : "";
}

/*---------------------------------------------------------------------------
**
*/
void
EqProfile::setName(const juce::String& profile_name)
{
    if (data_.isValid() && data_.hasProperty(XML_ATTR_PROFILE_NAME)) {
        data_.setProperty(XML_ATTR_PROFILE_NAME, profile_name, undo_manager_.get());
    }
}

/*---------------------------------------------------------------------------
**
*/
double
EqProfile::getBandGain(const Equalizer::BAND_ID band_id) const
{
    double ret = 0.0;

    if (data_.isValid()) {
        const juce::ValueTree& band = data_.getChildWithProperty(XML_ATTR_BAND_ID, band_id);

        if (band.isValid() && band.hasProperty(XML_ATTR_BAND_GAIN)) {
            ret = band.getProperty(XML_ATTR_BAND_GAIN);
        }
    }

    return ret;
}

/*---------------------------------------------------------------------------
**
*/
void
EqProfile::setBandGain(const Equalizer::BAND_ID band_id, const double gain) const
{
    if (!data_.isValid()) {
        return;
    }

    // Note the function is const and we're grabbing the band ValueTree to update by copy.
    // juce::ValueTree's are just references to a shared underlying container.
    // (Good news! because this helps us avoid the non-const l-value reference headache).
    juce::ValueTree band = data_.getChildWithProperty(XML_ATTR_BAND_ID, band_id);

    if (band.isValid()) {
        band.setProperty(XML_ATTR_BAND_GAIN, gain, undo_manager_.get());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
EqProfile::initialiseProfile()
{
    /*
    The default construction for an EQ Profile looks like this:

    (ValueTree)
    { "profile", {{ "name", "" }},
      {
        { "band", {{ "id", 0 }, { "gain", 0.0 }}},
        { "band", {{ "id", 1 }, { "gain", 0.0 }}},
        etc...
        { "band", {{ "id", 30 }, { "gain", 0.0 }}},
      }
    }

    (XML)
    <profile name="">
      <band id="0" gain="0.0"/>
      <band id="1" gain="0.0"/>
      etc...
      <band id="30" gain="0.0"/>
    </profile>
    */

    juce::ValueTree initial_data(XML_TAG_PROFILE);

    initial_data.setProperty(XML_ATTR_PROFILE_NAME, "", undo_manager_.get());

    for (int i = 0; i < Equalizer::NUM_BANDS; ++i) {
        juce::ValueTree band(XML_TAG_BAND);

        band.setProperty(XML_ATTR_BAND_ID, i, undo_manager_.get());
        band.setProperty(XML_ATTR_BAND_GAIN, 0.0, undo_manager_.get());

        initial_data.appendChild(band, undo_manager_.get());
    }

    data_ = initial_data;
}

/*---------------------------------------------------------------------------
** End of File
*/
