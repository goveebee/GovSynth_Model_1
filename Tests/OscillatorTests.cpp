#include "DSP/Oscillator.h"
#include <iostream>
#include <cassert>
#include <cmath>

void test_oscillator_output() {
    Oscillator osc;
    osc.prepare(44100.0);
    osc.setFrequency(440.0);
    osc.setLevel(1.0f);
    
    float sample = osc.process();
    std::cout << "Sample: " << sample << std::endl;
    assert(std::abs(sample) <= 1.0f);
    std::cout << "Oscillator output in bounds." << std::endl;
}

int main() {
    test_oscillator_output();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
