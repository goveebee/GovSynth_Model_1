#include "ParameterLayout.h"
#include "ParameterIDs.h"
#include <juce_audio_processors/juce_audio_processors.h>

juce::AudioProcessorValueTreeState::ParameterLayout ParameterLayout::createLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterChoice>(Params::Osc1Wave, "Osc 1 Wave", juce::StringArray{"Sine", "Triangle", "Saw", "Square"}, 2));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::Osc1Level, "Osc 1 Level", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.8f));

    params.push_back(std::make_unique<juce::AudioParameterChoice>(Params::Osc2Wave, "Osc 2 Wave", juce::StringArray{"Sine", "Triangle", "Saw", "Square"}, 2));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::Osc2Level, "Osc 2 Level", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.6f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::AmpAttack, "Amp Attack", juce::NormalisableRange<float>(0.001f, 5.0f, 0.001f, 0.3f), 0.01f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::AmpDecay, "Amp Decay", juce::NormalisableRange<float>(0.001f, 5.0f, 0.001f, 0.3f), 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::AmpSustain, "Amp Sustain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.7f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::AmpRelease, "Amp Release", juce::NormalisableRange<float>(0.001f, 10.0f, 0.001f, 0.3f), 0.4f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::MasterVolume, "Master Volume", juce::NormalisableRange<float>(-24.0f, 0.0f), -6.0f));

    return { params.begin(), params.end() };
}
