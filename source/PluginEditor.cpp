#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/look_and_feel/Theme.h"
#include "utility/GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , analyse_input_button_("Analyse Input", p.getApvts(), GuiParams::ANALYSE_INPUT)
    , show_fft_button_("Show Primary Signal Post EQ", p.getApvts(), GuiParams::SHOW_FFT)
    , theme_button_()
    , filter_res_graph_(p)
    , meter_group_(p)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(analyse_input_button_);
    addAndMakeVisible(show_fft_button_);
    addAndMakeVisible(theme_button_);
    addAndMakeVisible(filter_res_graph_);
    addAndMakeVisible(meter_group_);

    analyse_input_button_.addListener(this);
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
    analyse_input_button_.removeListener(this);
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
    juce::Rectangle< int > bounds                    = getLocalBounds();
    int                    bounds_height             = bounds.getHeight();
    int                    bounds_width              = bounds.getWidth();
    int                    top_controls_height       = static_cast< int >(std::floor(bounds_height * 0.05));
    int                    input_analysis_menu_width = static_cast< int >(std::floor(bounds_width * 0.3));
    int                    fft_menu_width            = static_cast< int >(std::floor(bounds_width * 0.6));
    int                    theme_button_width        = static_cast< int >(std::floor(bounds_width * 0.1));
    int                    graph_height              = static_cast< int >(std::floor(bounds_height * 0.65));
    int                    meters_height             = static_cast< int >(std::floor(bounds_height * 0.3));
    int                    meters_width              = static_cast< int >(std::floor(bounds_width * 0.75));

    analyse_input_button_.setBounds(0, 0, input_analysis_menu_width, top_controls_height);
    show_fft_button_.setBounds(analyse_input_button_.getRight(), 0, fft_menu_width, top_controls_height);
    theme_button_.setBounds(bounds.getRight() - theme_button_width, 0, theme_button_width, top_controls_height);
    filter_res_graph_.setBounds(0, top_controls_height, bounds_width, graph_height);
    meter_group_.setBounds(0, filter_res_graph_.getBottom(), meters_width, meters_height);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::buttonClicked(juce::Button* button)
{
    if (button == nullptr) {
        return;
    }

    if (button == &analyse_input_button_) {
        analyse_input_button_.getToggleState() ? processor_ref_.startInputAnalysis() : processor_ref_.stopInputAnalysis();
    }
    else if (button == &theme_button_) {
        repaint();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
