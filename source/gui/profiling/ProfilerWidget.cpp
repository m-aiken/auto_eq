#include "ProfilerWidget.h"

/*---------------------------------------------------------------------------
**
*/
ProfilerWidget::ProfilerWidget(MonoWaveform& mono_waveform_ref)
    : mono_waveform_ref_(mono_waveform_ref)
{
    addAndMakeVisible(mono_waveform_ref_);
}

/*---------------------------------------------------------------------------
**
*/
void
ProfilerWidget::resized()
{
    const auto bounds = getLocalBounds();

    const int waveform_width  = static_cast< int >(std::floor(bounds.getWidth() * 0.8));
    const int waveform_height = static_cast< int >(std::floor(bounds.getHeight() * 0.8));

    mono_waveform_ref_.setBounds(bounds.withSizeKeepingCentre(waveform_width, waveform_height));
}

/*---------------------------------------------------------------------------
** End of File
*/
