add_executable(EmilSynthTests 
    OscillatorTests.cpp
    ../Source/DSP/Oscillator.cpp
)
target_include_directories(EmilSynthTests PRIVATE ../Source)
