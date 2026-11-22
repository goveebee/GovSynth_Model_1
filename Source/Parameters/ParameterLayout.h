#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
class ParameterLayout
{
public:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
};
