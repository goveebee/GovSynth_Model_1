#include "Oscillator.h"


Oscillator::Oscillator() {}

void Oscillator::prepare(double sr)
{
    sampleRate = sr;
}

void Oscillator::setFrequency(double freq)
{
    increment = freq / sampleRate;
}

void Oscillator::setWaveform(Waveform w)
{
    waveform = w;
}

void Oscillator::setLevel(float l)
{
    level = l;
}

float Oscillator::polyBlep(double t, double dt)
{
    if (t < dt)
    {
        t /= dt;
        return static_cast<float>(t + t - t * t - 1.0);
    }
    else if (t > 1.0 - dt)
    {
        t = (t - 1.0) / dt;
        return static_cast<float>(t * t + t + t + 1.0);
    }
    return 0.0f;
}

float Oscillator::process()
{
    double t = phase;
    double dt = increment;
    float out = 0.0f;
    constexpr double PI = 3.14159265358979323846;

    switch (waveform)
    {
        case Waveform::Sine:
            out = static_cast<float>(std::sin(2.0 * PI * t));
            break;
        case Waveform::Triangle:
        {
            double v = 2.0 * std::abs(2.0 * (t - std::floor(t + 0.5))) - 1.0;
            out = static_cast<float>(v);
            break;
        }
        case Waveform::Saw:
        {
            double v = 2.0 * (t - std::floor(t + 0.5));
            out = static_cast<float>(v);
            out -= polyBlep(t, dt);
            break;
        }
        case Waveform::Square:
        {
            double v = (t < 0.5) ? 1.0 : -1.0;
            out = static_cast<float>(v);
            out -= polyBlep(t, dt);
            out -= polyBlep(t - 0.5, dt);
            break;
        }
    }

    phase += increment;
    if (phase >= 1.0) phase -= 1.0;

    return out * level * 0.5f;
}
