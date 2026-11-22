# Building

## Prerequisites

### Linux
* CMake 3.22+
* Ninja
* GCC 14 or Clang with C++20
* JUCE dependencies: ALSA, freetype2, fontconfig, GL

### Windows
* Windows 10/11 x64
* Visual Studio 2022 with C++ workload
* CMake 3.22+
* Ninja

## Linux

Configure with presets:
```bash
cmake --preset linux-debug
cmake --build build/linux-debug
```

Or manually:
```bash
cmake -S . -B build/linux-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++-14 -DCMAKE_C_COMPILER=gcc-14
cmake --build build/linux-debug --parallel
```

Artifacts:
* Standalone: `build/linux-debug/GovSynthModel1_artefacts/Debug/Standalone/GovSynth Model 1`
* VST3: `build/linux-debug/GovSynthModel1_artefacts/Debug/VST3/GovSynth Model 1.vst3`

## Windows

Configure with presets:
```powershell
cmake --preset windows-release
cmake --build build/windows-release --config Release
```

Or manually in Developer PowerShell:
```powershell
cmake -S . -B build/windows-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/windows-release --config Release
ctest --test-dir build/windows-release --output-on-failure
```

Artifacts:
* Standalone: `build/windows-release/GovSynthModel1_artefacts/Release/Standalone/GovSynth Model 1.exe`
* VST3: `build/windows-release/GovSynthModel1_artefacts/Release/VST3/GovSynth Model 1.vst3`

Notes:
* JUCE is pinned as submodule at tags/8.0.15
* Project uses C++20 and Ninja
* Do not build Windows binaries on Linux; use a native Windows runner

