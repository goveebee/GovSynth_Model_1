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

    void setOsc1Waveform(Oscillator::Waveform w);
    void setOsc2Waveform(Oscillator::Waveform w);
    void setOsc1Level(float level);
    void setOsc2Level(float level);
    void setOsc1Octave(int o);
    void setOsc1Semitone(int s);
    void setOsc1Detune(float cents);
    void setOsc2Octave(int o);
    void setOsc2Semitone(int s);
    void setOsc2Detune(float cents);
    void setAmpEnvelope(float attack, float decay, float sustain, float release);

private:
    Oscillator osc1;
    Oscillator osc2;
    Envelope env;
    double currentFreq = 440.0;

    int osc1Octave = 0;
    int osc1Semitone = 0;
    float osc1Detune = 0.0f;
    int osc2Octave = 0;
    int osc2Semitone = 0;
    float osc2Detune = 0.0f;

    double applyTuning(double baseFreq, int octave, int semitone, float cents) const;
};

