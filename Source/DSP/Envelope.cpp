#include "Envelope.h"

Envelope::Envelope() {}

void Envelope::prepare(double sr)
{
    sampleRate = sr;
}

void Envelope::setParameters(float a, float d, float s, float r)
{
    attack = a;
    decay = d;
    sustain = s;
    release = r;
    if (attack > 0.0f) attackInc = static_cast<float>(1.0 / (attack * sampleRate));
    if (decay > 0.0f) decayInc = static_cast<float>((1.0f - sustain) / (decay * sampleRate));
    if (release > 0.0f) releaseInc = static_cast<float>(1.0 / (release * sampleRate));
}

void Envelope::noteOn()
{
    state = State::Attack;
    level = 0.0f;
}

void Envelope::noteOff()
{
    if (state != State::Idle)
        state = State::Release;
}

float Envelope::process()
{
    switch (state)
    {
        case State::Idle:
            return 0.0f;
        case State::Attack:
            level += attackInc;
            if (level >= 1.0f)
            {
                level = 1.0f;
                state = State::Decay;
            }
            break;
        case State::Decay:
            level -= decayInc;
            if (level <= sustain)
            {
                level = sustain;
                state = State::Sustain;
            }
            break;
        case State::Sustain:
            break;
        case State::Release:
            level -= releaseInc;
            if (level <= 0.0f)
            {
                level = 0.0f;
                state = State::Idle;
            }
            break;
    }
    return level;
}
