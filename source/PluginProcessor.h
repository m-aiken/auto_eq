#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "dsp/EqParams.h"
#include "dsp/FilterFactory.h"
#include "dsp/MonoFftBuffer.h"
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

    typedef std::array< MonoFftBuffer, Global::FFT::NUM_BUFFERS > FftBuffers;

    juce::AudioProcessorValueTreeState& getApvts();

    FftBuffers& getFftBuffers();

    FilterFactory::MonoChain& getFilterChain();

    FilterFactory::BandSet& getFilterBands();

    float getMeterValue(Global::METER_TYPE meter_type, Global::Channels::CHANNEL_ID channel_id) const;

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();
    juce::AudioProcessorValueTreeState                         apvts_;

    FftBuffers fft_buffers_;

    FilterFactory::MonoChain filter_chain_left_;
    FilterFactory::MonoChain filter_chain_right_;

    FilterFactory::BandSet filter_bands_;

    void updateFilterCoefficients();

    template < typename T >
    void assignParameter(T& target, EqParams::PARAM_ID param_id)
    {
        auto apvts_param = dynamic_cast< T >(apvts_.getParameter(EqParams::getName(param_id)));

        if (apvts_param != nullptr) {
            target = apvts_param;
        }
    }

    typedef juce::SmoothedValue< float, juce::ValueSmoothingTypes::Linear > SmoothedFloat;

    static const double SMOOTHED_VALUE_RAMP_TIME_SECONDS;
    SmoothedFloat       peak_l_;
    SmoothedFloat       peak_r_;
    SmoothedFloat       rms_l_;
    SmoothedFloat       rms_r_;
    SmoothedFloat       lufs_l_;
    SmoothedFloat       lufs_r_;

    void setPeak(SmoothedFloat& val, juce::AudioBuffer< float >& buffer, Global::Channels::CHANNEL_ID channel);
    void setRms(SmoothedFloat& val, juce::AudioBuffer< float >& buffer, Global::Channels::CHANNEL_ID channel);
    void setLufs(SmoothedFloat& val, juce::AudioBuffer< float >& buffer, Global::Channels::CHANNEL_ID channel);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
