#include "SaveDialogBase.h"

/*---------------------------------------------------------------------------
**
*/
SaveDialogBase::SaveDialogBase(PluginProcessor&    processor_ref,
                               ButtonToolbar&      toolbar,
                               const juce::String& negative_button_text,
                               const juce::String& positive_button_text)
    : processor_ref_(processor_ref)
    , preset_manager_(processor_ref.getPresetManager())
    , toolbar_(toolbar)
    , name_entry_box_("preset name...")
    , negative_button_(negative_button_text)
    , positive_button_(positive_button_text)
    , duplicate_warning_("duplicate_preset_name_warning",
                         "Warning: a preset with that name already exists!",
                         juce::Justification::centred,
                         true)
{
    negative_button_.addListener(this);
    positive_button_.addListener(this);

    addAndMakeVisible(name_entry_box_);
    addAndMakeVisible(negative_button_);
    addAndMakeVisible(positive_button_);
    addAndMakeVisible(duplicate_warning_);

    name_entry_box_.resetTextColour();
    duplicate_warning_.setVisible(false);

    if (!preset_manager_.currentPresetHasDefaultName()) {
        name_entry_box_.setText(preset_manager_.getCurrentlyLoadedPresetName());
    }

    // The save button is disabled if the user clears the text (no name to save as).
    name_entry_box_.onTextChange = [&]() {
        const juce::String& text = name_entry_box_.getText();

        positive_button_.setEnabled(!text.isEmpty());

        // If the user is trying to use the name of a preset that already exists display a warning.
        const bool is_duplicate = preset_manager_.hasPresetWithName(text)
                                  && (text != preset_manager_.getCurrentlyLoadedPresetName());

        duplicate_warning_.setVisible(is_duplicate);
    };
}

/*---------------------------------------------------------------------------
**
*/
SaveDialogBase::~SaveDialogBase()
{
    negative_button_.removeListener(this);
    positive_button_.removeListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
SaveDialogBase::resized()
{
    const auto&   bounds        = getLocalBounds();
    const int     bounds_width  = bounds.getWidth();
    const int     bounds_height = bounds.getHeight();
    constexpr int padding       = 24;
    const auto padded_bounds = bounds.withSizeKeepingCentre(bounds_width - (padding * 2), bounds_height - (padding * 2));
    const auto text_box_height = static_cast< int >(std::floor(padded_bounds.getHeight() * 0.5));
    const auto button_height   = static_cast< int >(std::floor(text_box_height * 0.5));
    const auto button_width    = static_cast< int >(std::floor((padded_bounds.getWidth() * 0.5) - (padding * 0.25)));

    name_entry_box_.setBounds(padded_bounds.getX(), padded_bounds.getY(), padded_bounds.getWidth(), text_box_height);
    negative_button_.setBounds(padded_bounds.getX(), padded_bounds.getBottom() - button_height, button_width, button_height);
    positive_button_.setBounds(padded_bounds.getRight() - button_width,
                               padded_bounds.getBottom() - button_height,
                               button_width,
                               button_height);
    duplicate_warning_.setBounds(padded_bounds.getX(),
                                 name_entry_box_.getBottom(),
                                 padded_bounds.getWidth(),
                                 negative_button_.getY() - name_entry_box_.getBottom());
}

/*---------------------------------------------------------------------------
** End of File
*/
