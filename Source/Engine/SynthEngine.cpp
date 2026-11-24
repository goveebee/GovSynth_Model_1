#include "SynthEngine.h"

SynthEngine::SynthEngine()
{
    synth.addSound(new SynthSound());
    for (int i = 0; i < 8; ++i)
        synth.addVoice(new SynthVoice());
}

SynthEngine::~SynthEngine() {}

void SynthEngine::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    (void)samplesPerBlock;
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void SynthEngine::releaseResources()
{
}

void SynthEngine::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

void SynthEngine::setOsc1Waveform(int index)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setOsc1Waveform(static_cast<Oscillator::Waveform>(index));
    }
}

void SynthEngine::setOsc2Waveform(int index)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setOsc2Waveform(static_cast<Oscillator::Waveform>(index));
    }
}

void SynthEngine::setOsc1Level(float level)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setOsc1Level(level);
    }
}

void SynthEngine::setOsc2Level(float level)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setOsc2Level(level);
    }
}

void SynthEngine::setAmpEnvelope(float attack, float decay, float sustain, float release)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setAmpEnvelope(attack, decay, sustain, release);
    }
}
