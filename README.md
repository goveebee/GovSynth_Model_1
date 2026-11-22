# GovSynth Model 1

Classic analog-inspired polyphonic synthesizer VST3.

## Status

Milestone M1 - First audible instrument

## Build Requirements

- Linux x86-64 or Windows x86-64
- CMake 3.22+
- Ninja
- C++20-capable compiler (GCC 14+ / Clang 14+ / MSVC 2022)
- JUCE 8.x

### SUSE Linux Enterprise Server 15 SP7

Suggested packages:

```bash
sudo zypper refresh
sudo zypper install cmake ninja gcc14 gcc14-c++ libstdc++6-devel-gcc14 \
  pkg-config libX11-devel libXext-devel libXinerama-devel libXcursor-devel libXtst-devel \
  freetype2-devel fontconfig-devel Mesa-libGL-devel alsa-devel libjack-devel
```

## Build

### Linux

Using presets:
```bash
cmake --preset linux-debug
cmake --build build/linux-debug --parallel
ctest --test-dir build/linux-debug --output-on-failure
```

Or with GCC 14 via user preset:
```bash
cp CMakeUserPresets.json.example CMakeUserPresets.json
cmake --preset linux-debug-gcc14
cmake --build build/linux-debug --parallel
```

Artifacts:
* Standalone: `build/linux-debug/GovSynthModel1_artefacts/Debug/Standalone/GovSynth Model 1`
* VST3: `build/linux-debug/GovSynthModel1_artefacts/Debug/VST3/GovSynth Model 1.vst3`

### Windows

Prerequisites: Visual Studio 2022 with C++ workload, CMake, Ninja.

Using presets:
```powershell
cmake --preset windows-release
cmake --build build/windows-release --config Release
ctest --test-dir build/windows-release --output-on-failure
```

Or with VS2022 user preset:
```powershell
Copy-Item CMakeUserPresets.json.example CMakeUserPresets.json
cmake --preset windows-release-vs2022
cmake --build build/windows-release --config Release
```

Artifacts:
* Standalone: `build/windows-release/GovSynthModel1_artefacts/Release/Standalone/GovSynth Model 1.exe`
* VST3: `build/windows-release/GovSynthModel1_artefacts/Release/VST3/GovSynth Model 1.vst3`

## Testing

* Build succeeds with no warnings as errors
* Load VST3 in a DAW and verify MIDI note on/off produces sound
* Standalone launches and exposes parameters
* State save/restore works via APVTS

## Project Structure

See AGENTS.md for full architecture.

## License

See LICENSE

