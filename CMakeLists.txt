cmake_minimum_required(VERSION 3.22)
project(EmilSynth VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/CompilerWarnings.cmake)
include(cmake/Sanitizers.cmake)

# JUCE
set(JUCE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(JUCE_BUILD_TEACHING_TOOLS OFF CACHE BOOL "" FORCE)
add_subdirectory(JUCE)

# Plugin
juce_add_plugin(EmilSynth
    COMPANY_NAME "EmilSynth"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE EmIl
    PLUGIN_CODE EmSy
    FORMATS VST3 Standalone
    PRODUCT_NAME "Emil Synth"
    COPY_PLUGIN_AFTER_BUILD TRUE
)

target_sources(EmilSynth PRIVATE
    Source/Plugin/PluginProcessor.cpp
    Source/Plugin/PluginEditor.cpp
)

target_include_directories(EmilSynth PRIVATE
    Source
)

target_link_libraries(EmilSynth PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_devices
    juce::juce_dsp
    juce::juce_gui_basics
)

set_compiler_warnings(EmilSynth)

# Tests
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(Tests)
endif()
