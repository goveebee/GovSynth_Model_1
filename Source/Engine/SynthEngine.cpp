#include "SynthEngine.h"

SynthEngine::SynthEngine()
{
    synth.addSound(new SynthSound());
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

void SynthEngine::setWaveform(int index)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setWaveform(static_cast<Oscillator::Waveform>(index));
    }
}

void SynthEngine::setOscLevel(float level)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setOscLevel(level);
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
