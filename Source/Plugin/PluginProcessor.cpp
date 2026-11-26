#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../Parameters/ParameterIDs.h"

GovSynthModel1AudioProcessor::GovSynthModel1AudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", ParameterLayout::createLayout())
{
    keyboardState.addListener(this);

    auto logDir = juce::File("/srv/ee5/Documents/Projects/VST/GovSynth Model 1/logs");
    if (!logDir.exists())
        logDir.createDirectory();


    auto logFile = logDir.getChildFile("GovSynth.log");
    fileLogger.reset(new juce::FileLogger(logFile, "GovSynth log started", true));
    juce::Logger::setCurrentLogger(fileLogger.get());
    juce::Logger::writeToLog("GovSynthModel1AudioProcessor created");
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
    int osc1WaveIdx = static_cast<int>(params.getRawParameterValue(Params::Osc1Wave)->load());
    int osc2WaveIdx = static_cast<int>(params.getRawParameterValue(Params::Osc2Wave)->load());
    float osc1Level = params.getRawParameterValue(Params::Osc1Level)->load();
    float osc2Level = params.getRawParameterValue(Params::Osc2Level)->load();
    int osc1Octave = static_cast<int>(params.getRawParameterValue(Params::Osc1Octave)->load());
    int osc1Semitone = static_cast<int>(params.getRawParameterValue(Params::Osc1Semitone)->load());
    float osc1Detune = params.getRawParameterValue(Params::Osc1Detune)->load();
    int osc2Octave = static_cast<int>(params.getRawParameterValue(Params::Osc2Octave)->load());
    int osc2Semitone = static_cast<int>(params.getRawParameterValue(Params::Osc2Semitone)->load());
    float osc2Detune = params.getRawParameterValue(Params::Osc2Detune)->load();
    float ampAttack = params.getRawParameterValue(Params::AmpAttack)->load();
    float ampDecay = params.getRawParameterValue(Params::AmpDecay)->load();
    float ampSustain = params.getRawParameterValue(Params::AmpSustain)->load();
    float ampRelease = params.getRawParameterValue(Params::AmpRelease)->load();
    float masterDb = params.getRawParameterValue(Params::MasterVolume)->load();

    engine.setOsc1Waveform(osc1WaveIdx);
    engine.setOsc2Waveform(osc2WaveIdx);
    engine.setOsc1Level(osc1Level);
    engine.setOsc2Level(osc2Level);
    engine.setOsc1Octave(osc1Octave);
    engine.setOsc1Semitone(osc1Semitone);
    engine.setOsc1Detune(osc1Detune);
    engine.setOsc2Octave(osc2Octave);
    engine.setOsc2Semitone(osc2Semitone);
    engine.setOsc2Detune(osc2Detune);
    engine.setAmpEnvelope(ampAttack, ampDecay, ampSustain, ampRelease);

    engine.processBlock(buffer, midiMessages);

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

void GovSynthModel1AudioProcessor::handleNoteOn(juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    (void)source;
    (void)midiChannel;
    (void)velocity;
    engine.triggerNote(midiNoteNumber, true);
}

void GovSynthModel1AudioProcessor::handleNoteOff(juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    (void)source;
    (void)midiChannel;
    (void)velocity;
    engine.triggerNote(midiNoteNumber, false);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GovSynthModel1AudioProcessor();
}
