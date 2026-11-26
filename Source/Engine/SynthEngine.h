#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "SynthVoice.h"
#include "SynthSound.h"

class SynthEngine
{
public:
    SynthEngine();
    ~SynthEngine();

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

    void setOsc1Waveform(int index);
    void setOsc2Waveform(int index);
    void setOsc1Level(float level);
    void setOsc2Level(float level);
    void setOsc1Octave(int o);
    void setOsc1Semitone(int s);
    void setOsc1Detune(float c);
    void setOsc2Octave(int o);
    void setOsc2Semitone(int s);
    void setOsc2Detune(float c);
    void setAmpEnvelope(float attack, float decay, float sustain, float release);
    void triggerNote(int noteNumber, bool on);


private:
    juce::Synthesiser synth;
};

