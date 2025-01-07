#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();

    void drawRotarySlider(juce::Graphics& g,
                          int             x,
                          int             y,
                          int             width,
                          int             height,
                          float           slider_pos_proportional,
                          float           rotary_start_angle,
                          float           rotary_end_angle,
                          juce::Slider&   slider) override;

    void drawLinearSlider(juce::Graphics&           g,
                          int                       x,
                          int                       y,
                          int                       width,
                          int                       height,
                          float                     slider_pos,
                          float                     min_slider_pos,
                          float                     max_slider_pos,
                          juce::Slider::SliderStyle slider_style,
                          juce::Slider&             slider) override;

    void fillTextEditorBackground(juce::Graphics& g, int width, int height, juce::TextEditor& editor) override;

    void drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& editor) override;

    void drawPopupMenuBackgroundWithOptions(juce::Graphics&                 g,
                                            int                             width,
                                            int                             height,
                                            const juce::PopupMenu::Options& options) override;

    void drawPopupMenuItemWithOptions(juce::Graphics&                 g,
                                      const juce::Rectangle< int >&   area,
                                      bool                            is_highlighted,
                                      const juce::PopupMenu::Item&    item,
                                      const juce::PopupMenu::Options& options) override;

    int getPopupMenuBorderSize() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
