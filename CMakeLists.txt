cmake_minimum_required(VERSION 3.22)
project(ReLufs VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

target_sources(${PROJECT_NAME}
        PRIVATE
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        source/dsp/BandUpdater.cpp
        source/dsp/BandParameterUpdater.cpp
        source/dsp/Equalizer.cpp
        source/dsp/InputAnalysisFilter.cpp
        source/dsp/MonoFftBuffer.cpp
        source/gui/gain_control/UnityGainWidget.cpp
        source/gui/look_and_feel/CustomLookAndFeel.cpp
        source/gui/look_and_feel/Theme.cpp
        source/gui/meters/MeterCanvas.cpp
        source/gui/meters/MeterDbScale.cpp
        source/gui/meters/MeterGroup.cpp
        source/gui/meters/MeterLabel.cpp
        source/gui/meters/MonoMeter.cpp
        source/gui/meters/StereoMeter.cpp
        source/gui/response_graph/DecibelMarkers.cpp
        source/gui/response_graph/EqBandSlider.cpp
        source/gui/response_graph/FilterMagnitudesCalculator.cpp
        source/gui/response_graph/FilterResponseBands.cpp
        source/gui/response_graph/FilterResponseCanvas.cpp
        source/gui/response_graph/FilterResponseGraph.cpp
        source/gui/response_graph/FrequencyMarkers.cpp
        source/gui/response_graph/MonoFftPath.cpp
        source/gui/response_graph/MonoFftPathProducer.cpp
        source/gui/widgets/MenuButton.cpp
        source/gui/widgets/PowerButton.cpp
        source/gui/widgets/RecordButton.cpp
        source/gui/widgets/RotaryControl.cpp
        source/gui/widgets/spinbox/SpinBox.cpp
        source/gui/widgets/spinbox/SpinBoxButton.cpp
        source/gui/widgets/spinbox/SpinBoxTextBox.cpp
        source/gui/widgets/ThemeButton.cpp
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
