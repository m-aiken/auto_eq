#pragma once

#include <JuceHeader.h>

#include "BandParameterUpdater.h"
#include "BandUpdater.h"
#include "Ebu128LoudnessMeter.h"
#include "Equalizer.h"
#include "GlobalConstants.h"
#include "InputAnalysisFilter.h"
#include "MonoFftBuffer.h"
#include "UnityGainCalculator.h"

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

    juce::AudioProcessorValueTreeState& getApvts();

    typedef juce::SmoothedValue< float, juce::ValueSmoothingTypes::Linear > SmoothedFloat;
    typedef std::array< MonoFftBuffer, Global::FFT::NUM_BUFFERS >           FftBuffers;

    FftBuffers&           getFftBuffers();
    Equalizer::MonoChain& getFilterChain();

    float getInputGainValue() const;

    float getMeterValue(const Global::Meters::METER_TYPE meter_type) const;

    void resetLufsModule();

    void startInputAnalysis();
    void stopInputAnalysis();

    void startUnityGainCalculation();
    void stopUnityGainCalculation();

private:
    bool booleanParameterEnabled(GuiParams::PARAM_ID param_id) const;

    void         updateFilterCoefficients();
    void         updateInputGainValue(const juce::AudioBuffer< float >& buffer);
    void         updateLufsValues(const juce::AudioBuffer< float >& dummy_buffer);
    void         applyInputTrim(juce::AudioBuffer< float >& buffer) const;
    void         applyMasterGain(juce::AudioBuffer< float >& buffer);
    static float getNormalisedValue(float full_range_value);

    static juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();

private:
    juce::AudioProcessorValueTreeState apvts_;

    static const double METER_DB_RAMP_TIME_SECONDS;

    InputAnalysisFilter  input_analysis_filter_;
    BandUpdater          band_updater_;
    BandParameterUpdater band_parameter_updater_;
    FftBuffers           fft_buffers_;

    Equalizer::MonoChain filter_chain_left_;
    Equalizer::MonoChain filter_chain_right_;

    SmoothedFloat input_gain_value_;

    // LUFS values.
    std::array< SmoothedFloat, Global::Meters::NUM_LOUDNESS_METERS > loudness_values_;

    juce::AudioBuffer< float > empty_buffer_;  //! Used to clear the meters when the plugin is disabled.

    UnityGainCalculator unity_gain_calculator_;

    Ebu128LoudnessMeter lufs_module_;

#ifdef TEST_FFT_ACCURACY
    juce::dsp::Oscillator< float > fft_test_tone_;
    juce::dsp::Gain< float >       fft_test_tone_gain_;
#endif
    void updateFftTestTone();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
