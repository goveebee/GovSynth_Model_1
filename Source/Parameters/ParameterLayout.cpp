#include "ParameterLayout.h"
#include "ParameterIDs.h"
#include <juce_audio_processors/juce_audio_processors.h>

juce::AudioProcessorValueTreeState::ParameterLayout ParameterLayout::createLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterChoice>(Params::Osc1Wave, "Osc 1 Wave", juce::StringArray{"Sine", "Triangle", "Saw"}, 2));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::Osc1Level, "Osc 1 Level", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterInt>(Params::Osc1Octave, "Osc 1 Octave", -2, 2, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>(Params::Osc1Semitone, "Osc 1 Semitone", -12, 12, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::Osc1Detune, "Osc 1 Detune", juce::NormalisableRange<float>(-50.0f, 50.0f), 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterChoice>(Params::Osc2Wave, "Osc 2 Wave", juce::StringArray{"Sine", "Triangle", "Saw"}, 2));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::Osc2Level, "Osc 2 Level", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.6f));
    params.push_back(std::make_unique<juce::AudioParameterInt>(Params::Osc2Octave, "Osc 2 Octave", -2, 2, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>(Params::Osc2Semitone, "Osc 2 Semitone", -12, 12, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::Osc2Detune, "Osc 2 Detune", juce::NormalisableRange<float>(-50.0f, 50.0f), 5.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::AmpAttack, "Amp Attack", juce::NormalisableRange<float>(0.001f, 5.0f, 0.001f, 0.3f), 0.01f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::AmpDecay, "Amp Decay", juce::NormalisableRange<float>(0.001f, 5.0f, 0.001f, 0.3f), 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::AmpSustain, "Amp Sustain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.7f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::AmpRelease, "Amp Release", juce::NormalisableRange<float>(0.001f, 10.0f, 0.001f, 0.3f), 0.4f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(Params::MasterVolume, "Master Volume", juce::NormalisableRange<float>(-24.0f, 0.0f), -6.0f));

    return { params.begin(), params.end() };
}
