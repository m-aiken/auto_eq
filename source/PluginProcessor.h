#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "dsp/CutBand.h"
#include "dsp/EqParams.h"
#include "dsp/FilterFactory.h"
#include "dsp/MonoFftBuffer.h"
#include "dsp/PeakBand.h"
#include "dsp/ShelfBand.h"
#include "utility/GlobalConstants.h"

class PluginProcessor final : public juce::AudioProcessor
{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay(double sample_rate, int samples_per_block) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer< float >& buffer, juce::MidiBuffer& midi_messages) override;
    using AudioProcessor::processBlock;

    juce::AudioProcessorEditor* createEditor() override;
    bool                        hasEditor() const override;

    const juce::String getName() const override;

    bool   acceptsMidi() const override;
    bool   producesMidi() const override;
    bool   isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int                getNumPrograms() override;
    int                getCurrentProgram() override;
    void               setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void               changeProgramName(int index, const juce::String& new_name) override;

    void getStateInformation(juce::MemoryBlock& dest_data) override;
    void setStateInformation(const void* data, int size_in_bytes) override;

    typedef std::array< MonoFftBuffer, Global::Channels::NUM_INPUTS > FftBuffers;

    FftBuffers& getFftBuffers();

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();
    juce::AudioProcessorValueTreeState                         apvts_;

    FftBuffers fft_buffers_;

    FilterFactory::MonoChain filter_chain_left_;
    FilterFactory::MonoChain filter_chain_right_;

    CutBand   low_cut_;
    ShelfBand low_shelf_;
    PeakBand  peak_1_;
    PeakBand  peak_2_;
    PeakBand  peak_3_;
    PeakBand  peak_4_;
    PeakBand  peak_5_;
    ShelfBand high_shelf_;
    CutBand   high_cut_;

    template < typename T >
    void assignParameter(T target, EqParams::PARAM_ID param_id)
    {
        auto apvts_param = dynamic_cast< T >(apvts_.getParameter(EqParams::getName(param_id)));

        if (apvts_param != nullptr) {
            target = apvts_param;
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
