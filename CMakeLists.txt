cmake_minimum_required(VERSION 3.22)
project(GovSynthModel1 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/CompilerWarnings.cmake)
include(cmake/Sanitizers.cmake)

add_compile_definitions(JUCE_VST3_CAN_REPLACE_VST2=0)

# JUCE
set(JUCE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(JUCE_BUILD_TEACHING_TOOLS OFF CACHE BOOL "" FORCE)
add_subdirectory(JUCE)

# Plugin
juce_add_plugin(GovSynthModel1
    COMPANY_NAME "GovSynth"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE GovS
    PLUGIN_CODE GovM
    FORMATS VST3 Standalone
    PRODUCT_NAME "GovSynthModel1"
    COPY_PLUGIN_AFTER_BUILD TRUE
)

target_sources(GovSynthModel1 PRIVATE
    Source/Plugin/PluginProcessor.cpp
    Source/Plugin/PluginEditor.cpp
    Source/Parameters/ParameterLayout.cpp
    Source/Engine/SynthEngine.cpp
    Source/Engine/SynthVoice.cpp
    Source/Engine/SynthSound.cpp
    Source/DSP/Oscillator.cpp
    Source/DSP/Envelope.cpp
)

target_include_directories(GovSynthModel1 PRIVATE
    Source
)

target_link_libraries(GovSynthModel1 PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_devices
    juce::juce_dsp
    juce::juce_gui_basics
)

set_compiler_warnings(GovSynthModel1)

# Tests
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(Tests)
endif()
