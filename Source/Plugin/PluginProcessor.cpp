#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../Parameters/ParameterIDs.h"

GovSynthModel1AudioProcessor::GovSynthModel1AudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", ParameterLayout::createLayout())
{
}

GovSynthModel1AudioProcessor::~GovSynthModel1AudioProcessor() {}

void GovSynthModel1AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    engine.prepareToPlay(sampleRate, samplesPerBlock);
}

void GovSynthModel1AudioProcessor::releaseResources()
{
    engine.releaseResources();
}

bool GovSynthModel1AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    return true;
}

void GovSynthModel1AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    auto& params = apvts;
    engine.setOsc1Waveform(static_cast<int>(params.getRawParameterValue(Params::Osc1Wave)->load()));
    engine.setOsc2Waveform(static_cast<int>(params.getRawParameterValue(Params::Osc2Wave)->load()));
    engine.setOsc1Level(params.getRawParameterValue(Params::Osc1Level)->load());
    engine.setOsc2Level(params.getRawParameterValue(Params::Osc2Level)->load());
    engine.setAmpEnvelope(
        params.getRawParameterValue(Params::AmpAttack)->load(),
        params.getRawParameterValue(Params::AmpDecay)->load(),
        params.getRawParameterValue(Params::AmpSustain)->load(),
        params.getRawParameterValue(Params::AmpRelease)->load()
    );

    engine.processBlock(buffer, midiMessages);

    float masterDb = params.getRawParameterValue(Params::MasterVolume)->load();
    float masterGain = juce::Decibels::decibelsToGain(masterDb);
    buffer.applyGain(masterGain);
}

juce::AudioProcessorEditor* GovSynthModel1AudioProcessor::createEditor()
{
    return new GovSynthModel1AudioProcessorEditor(*this);
}

void GovSynthModel1AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(apvts.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void GovSynthModel1AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState && xmlState->hasTagName(apvts.state.getType()))
        apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GovSynthModel1AudioProcessor();
}
