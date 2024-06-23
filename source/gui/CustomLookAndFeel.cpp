#include "CustomLookAndFeel.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
CustomLookAndFeel::CustomLookAndFeel()
{
}

/*---------------------------------------------------------------------------
**
*/
void
CustomLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                    int             x,
                                    int             y,
                                    int             width,
                                    int             height,
                                    float           slider_pos_proportional,
                                    float           rotary_start_angle,
                                    float           rotary_end_angle,
                                    juce::Slider&   slider)
{
    juce::Rectangle< float > bounds(x, y, width, height);
    auto                     radius         = juce::jmin(width, height) * 0.5;
    float                    path_thickness = 4.f;
    auto                     arc_radius     = radius - (path_thickness * 0.5);

    // Fill.
    g.setColour(Theme::getColour(Theme::ROTARY_FILL));

    juce::Path fill_path;

    fill_path.addCentredArc(bounds.getCentreX(),
                            bounds.getCentreY(),
                            arc_radius,
                            arc_radius,
                            0.f,
                            rotary_start_angle,
                            rotary_end_angle,
                            true);

    g.strokePath(fill_path, juce::PathStrokeType(path_thickness));

    // Arc.
    g.setColour(Theme::getColour(Theme::ROTARY_ARC));

    juce::Path arc_path;

    arc_path.addCentredArc(bounds.getCentreX(),
                           bounds.getCentreY(),
                           arc_radius,
                           arc_radius,
                           0.f,
                           rotary_start_angle,
                           slider_pos_proportional,
                           true);

    g.strokePath(arc_path, juce::PathStrokeType(path_thickness));
}

/*---------------------------------------------------------------------------
** End of File
*/
