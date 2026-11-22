#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    (void)samplesPerBlock;
    osc.prepare(sampleRate);
    env.prepare(sampleRate);
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    (void)velocity; (void)sound; (void)currentPitchWheelPosition;
    currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    osc.setFrequency(currentFreq);
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
        float oscSample = osc.process();
        float envSample = env.process();
        float out = oscSample * envSample;

        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        {
            outputBuffer.addSample(channel, startSample + sample, out);
        }

        if (envSample <= 0.0001f && env.process() == 0.0f)
        {
            clearCurrentNote();
            break;
        }
    }
}

void SynthVoice::setWaveform(Oscillator::Waveform w)
{
    osc.setWaveform(w);
}

void SynthVoice::setOscLevel(float level)
{
    osc.setLevel(level);
}

void SynthVoice::setAmpEnvelope(float attack, float decay, float sustain, float release)
{
    env.setParameters(attack, decay, sustain, release);
}
