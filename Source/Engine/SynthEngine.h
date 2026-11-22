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

    void setWaveform(int index);
    void setOscLevel(float level);
    void setAmpEnvelope(float attack, float decay, float sustain, float release);

private:
    juce::Synthesiser synth;
};

