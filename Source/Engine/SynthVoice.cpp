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

double SynthVoice::applyTuning(double baseFreq, int octave, int semitone, float cents) const
{
    double freq = baseFreq;
    freq *= std::pow(2.0, octave + semitone / 12.0 + cents / 1200.0);
    return freq;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    (void)velocity; (void)sound; (void)currentPitchWheelPosition;
    currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    osc1.setFrequency(applyTuning(currentFreq, osc1Octave, osc1Semitone, osc1Detune));
    osc2.setFrequency(applyTuning(currentFreq, osc2Octave, osc2Semitone, osc2Detune));
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
    juce::Logger::writeToLog("SynthVoice setOsc1Waveform w=" + juce::String(static_cast<int>(w)));
    osc1.setWaveform(w);
}

void SynthVoice::setOsc2Waveform(Oscillator::Waveform w)
{
    juce::Logger::writeToLog("SynthVoice setOsc2Waveform w=" + juce::String(static_cast<int>(w)));
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

void SynthVoice::setOsc1Octave(int o) { osc1Octave = o; }
void SynthVoice::setOsc1Semitone(int s) { osc1Semitone = s; }
void SynthVoice::setOsc1Detune(float cents) { osc1Detune = cents; }
void SynthVoice::setOsc2Octave(int o) { osc2Octave = o; }
void SynthVoice::setOsc2Semitone(int s) { osc2Semitone = s; }
void SynthVoice::setOsc2Detune(float cents) { osc2Detune = cents; }

void SynthVoice::setAmpEnvelope(float attack, float decay, float sustain, float release)
{
    env.setParameters(attack, decay, sustain, release);
}
