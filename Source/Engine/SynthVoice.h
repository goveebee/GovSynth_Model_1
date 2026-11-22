#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "../DSP/Oscillator.h"
#include "../DSP/Envelope.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void setWaveform(Oscillator::Waveform w);
    void setOscLevel(float level);
    void setAmpEnvelope(float attack, float decay, float sustain, float release);

private:
    Oscillator osc;
    Envelope env;
    double currentFreq = 440.0;
};

