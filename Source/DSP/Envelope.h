#pragma once

class Envelope
{
public:
    enum class State { Idle, Attack, Decay, Sustain, Release };

    Envelope();
    void prepare(double sampleRate);
    void setParameters(float attack, float decay, float sustain, float release);
    void noteOn();
    void noteOff();
    float process();

private:
    double sampleRate = 44100.0;
    State state = State::Idle;
    float attack = 0.01f, decay = 0.3f, sustain = 0.7f, release = 0.4f;
    float level = 0.0f;
    float attackInc = 0.0f, decayInc = 0.0f, releaseInc = 0.0f;
};

