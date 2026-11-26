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
    juce::Logger::writeToLog("SynthEngine setOsc1Waveform index=" + juce::String(index));
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setOsc1Waveform(static_cast<Oscillator::Waveform>(index));
    }
}

void SynthEngine::setOsc2Waveform(int index)
{
    juce::Logger::writeToLog("SynthEngine setOsc2Waveform index=" + juce::String(index));
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

void SynthEngine::setOsc1Octave(int o)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i))) v->setOsc1Octave(o);
}
void SynthEngine::setOsc1Semitone(int s)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i))) v->setOsc1Semitone(s);
}
void SynthEngine::setOsc1Detune(float c)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i))) v->setOsc1Detune(c);
}
void SynthEngine::setOsc2Octave(int o)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i))) v->setOsc2Octave(o);
}
void SynthEngine::setOsc2Semitone(int s)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i))) v->setOsc2Semitone(s);
}
void SynthEngine::setOsc2Detune(float c)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i))) v->setOsc2Detune(c);
}

void SynthEngine::setAmpEnvelope(float attack, float decay, float sustain, float release)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            v->setAmpEnvelope(attack, decay, sustain, release);
    }
}

void SynthEngine::triggerNote(int noteNumber, bool on)
{
    if (on)
        synth.noteOn(1, noteNumber, 0.8f);
    else
        synth.noteOff(1, noteNumber, 0.8f, true);
}
