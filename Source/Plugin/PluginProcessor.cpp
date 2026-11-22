#include "PluginProcessor.h"
#include "PluginEditor.h"

EmilSynthAudioProcessor::EmilSynthAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

EmilSynthAudioProcessor::~EmilSynthAudioProcessor() {}

void EmilSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}
void EmilSynthAudioProcessor::releaseResources() {}

bool EmilSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    return true;
}

void EmilSynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        buffer.clear(channel, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* EmilSynthAudioProcessor::createEditor()
{
    return new EmilSynthAudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CREATE_PLUGIN_FILTER(EmilSynthAudioProcessor)
