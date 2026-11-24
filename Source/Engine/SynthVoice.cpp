#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    (void)samplesPerBlock;
    osc1.prepare(sampleRate);
    osc2.prepare(sampleRate);
    env.prepare(sampleRate);
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    (void)velocity; (void)sound; (void)currentPitchWheelPosition;
    currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    osc1.setFrequency(currentFreq);
    osc2.setFrequency(currentFreq * 1.01); // slight detune
    env.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    (void)velocity; (void)allowTailOff;
    env.noteOff();
    clearCurrentNote();
}

void SynthVoice::controllerMoved(int controllerNumber, int newValue) 
{ 
    (void)controllerNumber; (void)newValue; 
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) 
{ 
    (void)newPitchWheelValue; 
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
        return;

    for (int sample = 0; sample < numSamples; ++sample)
    {
        float osc1Sample = osc1.process();
        float osc2Sample = osc2.process();
        float envSample = env.process();
        float out = (osc1Sample + osc2Sample) * 0.5f * envSample;

        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        {
            outputBuffer.addSample(channel, startSample + sample, out);
        }

        if (envSample <= 0.0001f)
        {
            clearCurrentNote();
            break;
        }
    }
}

void SynthVoice::setOsc1Waveform(Oscillator::Waveform w)
{
    osc1.setWaveform(w);
}

void SynthVoice::setOsc2Waveform(Oscillator::Waveform w)
{
    osc2.setWaveform(w);
}

void SynthVoice::setOsc1Level(float level)
{
    osc1.setLevel(level);
}

void SynthVoice::setOsc2Level(float level)
{
    osc2.setLevel(level);
}

void SynthVoice::setAmpEnvelope(float attack, float decay, float sustain, float release)
{
    env.setParameters(attack, decay, sustain, release);
}
