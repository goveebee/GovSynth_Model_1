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
    void setAmpEnvelope(float attack, float decay, float sustain, float release);

private:
    juce::Synthesiser synth;
};

