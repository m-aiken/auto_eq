cmake_minimum_required(VERSION 3.23)
project(ReLufs VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(JUCE_COPY_PLUGIN_AFTER_BUILD ON)

#
# Dependencies.
# 1. Create a dependencies folder in our project.
# 2. Get CPM (cmake package manager).
# 3. Use CPM to get JUCE.
#
set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
include(cmake/get_cpm.cmake)
include(cmake/get_juce.cmake)

#
# Plugin configuration.
#
juce_add_plugin(${PROJECT_NAME}
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME maiken                         # Specify the name of the plugin's author
        IS_SYNTH FALSE                              # Is this a synth or an effect?
        NEEDS_MIDI_INPUT FALSE                      # Does the plugin need midi input?
        NEEDS_MIDI_OUTPUT FALSE                     # Does the plugin need midi output?
        IS_MIDI_EFFECT FALSE                        # Is this plugin a MIDI effect?
        # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
        # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE        # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE MAPC               # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE P008                            # A unique four-character plugin id with exactly one upper-case character
        # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
        FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        PRODUCT_NAME "Reactive LUFS Normalisation") # The name of the final executable, which can differ from the target name

juce_generate_juce_header(${PROJECT_NAME})

set(PROJECT_SOURCES
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        source/dsp/AudioBufferFifo.cpp
        source/dsp/BandUpdater.cpp
        source/dsp/BandParameterUpdater.cpp
        source/dsp/Equalizer.cpp
        source/dsp/InputAnalysisFilter.cpp
        source/dsp/MonoFftBuffer.cpp
        source/dsp/UnityGainCalculator.cpp
        source/gui/eq_intensity/EqIntensity.cpp
        source/gui/look_and_feel/CustomLookAndFeel.cpp
        source/gui/look_and_feel/Theme.cpp
        source/gui/master_gain/MasterGain.cpp
        source/gui/meters/LufsLabelGroup.cpp
        source/gui/meters/LufsMeterGroup.cpp
        source/gui/meters/LufsMetersWidget.cpp
        source/gui/meters/MeterCanvas.cpp
        source/gui/meters/MeterDbScale.cpp
        source/gui/meters/MonoMeter.cpp
        source/gui/mode_selector/ModeSelector.cpp
        source/gui/profiling/MonoWaveform.cpp
        source/gui/profiling/ProfilerInputMeter.cpp
        source/gui/profiling/ProfilerInputWidget.cpp
        source/gui/profiling/ProfilerWidget.cpp
        source/gui/response_graph/DecibelMarkers.cpp
        source/gui/response_graph/EqBandSlider.cpp
        source/gui/response_graph/FilterMagnitudesCalculator.cpp
        source/gui/response_graph/FilterResponseBands.cpp
        source/gui/response_graph/FilterResponseCanvas.cpp
        source/gui/response_graph/FilterResponseGraph.cpp
        source/gui/response_graph/FrequencyMarkers.cpp
        source/gui/response_graph/MonoFftPath.cpp
        source/gui/response_graph/MonoFftPathProducer.cpp
        source/gui/toolbar/ButtonToolbar.cpp
        source/gui/toolbar/PluginEnablementButton.cpp
        source/gui/toolbar/ThemeButton.cpp
        source/gui/transport/TransportButton.cpp
        source/gui/transport/TransportGroup.cpp
        source/gui/widgets/CustomTextButton.cpp
        source/gui/widgets/CustomTextToggleButton.cpp
        source/gui/widgets/DisableableLabel.cpp
        source/gui/widgets/RotaryControl.cpp
        source/gui/widgets/ToggleSwitch.cpp

        source/third_party/klangfreund_lufs_meter/Ebu128LoudnessMeter.cpp
        source/third_party/klangfreund_lufs_meter/filters/SecondOrderIIRFilter.cpp
        )

set(PROJECT_HEADERS
        source/PluginEditor.h
        source/PluginProcessor.h
        source/dsp/AudioBufferFifo.h
        source/dsp/BandUpdater.h
        source/dsp/BandParameterUpdater.h
        source/dsp/Equalizer.h
        source/dsp/InputAnalysisFilter.h
        source/dsp/MonoFftBuffer.h
        source/dsp/UnityGainCalculator.h
        source/gui/eq_intensity/EqIntensity.h
        source/gui/look_and_feel/CustomLookAndFeel.h
        source/gui/look_and_feel/Theme.h
        source/gui/master_gain/MasterGain.h
        source/gui/meters/LufsLabelGroup.h
        source/gui/meters/LufsMeterGroup.h
        source/gui/meters/LufsMetersWidget.h
        source/gui/meters/MeterCanvas.h
        source/gui/meters/MeterDbScale.h
        source/gui/meters/MonoMeter.h
        source/gui/mode_selector/ModeSelector.h
        source/gui/profiling/MonoWaveform.h
        source/gui/profiling/ProfilerInputMeter.h
        source/gui/profiling/ProfilerInputWidget.h
        source/gui/profiling/ProfilerWidget.h
        source/gui/response_graph/DecibelMarkers.h
        source/gui/response_graph/EqBandSlider.h
        source/gui/response_graph/FilterMagnitudesCalculator.h
        source/gui/response_graph/FilterResponseBands.h
        source/gui/response_graph/FilterResponseCanvas.h
        source/gui/response_graph/FilterResponseGraph.h
        source/gui/response_graph/FrequencyMarkers.h
        source/gui/response_graph/MonoFftPath.h
        source/gui/response_graph/MonoFftPathProducer.h
        source/gui/toolbar/ButtonToolbar.h
        source/gui/toolbar/PluginEnablementButton.h
        source/gui/toolbar/ThemeButton.h
        source/gui/transport/TransportButton.h
        source/gui/transport/TransportGroup.h
        source/gui/widgets/CustomTextButton.h
        source/gui/widgets/CustomTextToggleButton.h
        source/gui/widgets/DisableableLabel.h
        source/gui/widgets/RotaryControl.h
        source/gui/widgets/ToggleSwitch.h
        source/utility/GlobalConstants.h

        source/third_party/klangfreund_lufs_meter/Ebu128LoudnessMeter.h
        source/third_party/klangfreund_lufs_meter/filters/SecondOrderIIRFilter.h
        )

target_sources(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/source/dsp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/eq_intensity
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/look_and_feel
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/master_gain
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/meters
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/mode_selector
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/profiling
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/response_graph
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/toolbar
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/transport
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/widgets
        ${CMAKE_CURRENT_SOURCE_DIR}/source/utility

        ${CMAKE_CURRENT_SOURCE_DIR}/source/third_party/klangfreund_lufs_meter
        ${CMAKE_CURRENT_SOURCE_DIR}/source/third_party/klangfreund_lufs_meter/filters
        )

# JUCE modules make use of compile definitions to switch certain features on/off.
# If there's a particular feature you need that's not on by default,
# check the module header for the correct flag to set here.
target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

# juce_add_binary_data(ReLufsPluginData SOURCES ...)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        # ReLufsPluginData
        juce::juce_audio_utils
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
