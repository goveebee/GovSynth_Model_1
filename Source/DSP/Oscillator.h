#pragma once
#include <cmath>

class Oscillator
{
public:
    enum class Waveform { Sine, Triangle, Saw, Square };

    Oscillator();
    void prepare(double sampleRate);
    void setFrequency(double freq);
    void setWaveform(Waveform w);
    void setLevel(float level);
    float process();

private:
    double sampleRate = 44100.0;
    double phase = 0.0;
    double increment = 0.0;
    Waveform waveform = Waveform::Saw;
    float level = 1.0f;

    static float polyBlep(double t, double dt);
};

