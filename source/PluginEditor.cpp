#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/look_and_feel/Theme.h"

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , fft_menu_(p.getApvts())
    , theme_button_()
    , filter_res_graph_(p)
    , intensity_control_(p.getApvts())
    , meter_group_(p)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(fft_menu_);
    addAndMakeVisible(theme_button_);
    addAndMakeVisible(filter_res_graph_);
    addAndMakeVisible(intensity_control_);
    addAndMakeVisible(meter_group_);

    theme_button_.addListener(this);

    setResizable(true, true);
    setResizeLimits(768, 400, 1100, 600);
    setSize(1000, 500);
}

/*---------------------------------------------------------------------------
**
*/
PluginEditor::~PluginEditor()
{
    theme_button_.removeListener(this);
    setLookAndFeel(nullptr);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(Theme::getColour(Theme::MAIN_BG));
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::resized()
{
    juce::Rectangle< int > bounds              = getLocalBounds();
    int                    bounds_height       = bounds.getHeight();
    int                    bounds_width        = bounds.getWidth();
    int                    top_controls_height = static_cast< int >(std::floor(bounds_height * 0.05));
    int                    fft_menu_width      = static_cast< int >(std::floor(bounds_width * 0.8));
    int                    theme_button_width  = static_cast< int >(std::floor(bounds_width * 0.1));
    int                    graph_height        = static_cast< int >(std::floor(bounds_height * 0.65));
    int                    meters_height       = static_cast< int >(std::floor(bounds_height * 0.3));
    int                    meters_width        = static_cast< int >(std::floor(bounds_width * 0.75));
    int                    intensity_width     = static_cast< int >(std::floor(bounds_width * 0.25));

    fft_menu_.setBounds(0, 0, fft_menu_width, top_controls_height);
    theme_button_.setBounds(bounds.getRight() - theme_button_width, 0, theme_button_width, top_controls_height);
    filter_res_graph_.setBounds(0, top_controls_height, bounds_width, graph_height);
    intensity_control_.setBounds(0, filter_res_graph_.getBottom(), intensity_width, meters_height);
    meter_group_.setBounds(intensity_control_.getRight(), filter_res_graph_.getBottom(), meters_width, meters_height);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::buttonClicked(juce::Button* button)
{
    if (button != nullptr && button == &theme_button_) {
        repaint();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
