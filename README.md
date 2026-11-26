# GovSynthModel1

Classic analog-inspired polyphonic synthesizer VST3.

## Status

Milestone M2 - Dual oscillator polyphony with labeled UI

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

Note: GCC 7.5 is default on SLES 15 SP7 and does not support C++20. Use `g++-14` via the `linux-release-sles` preset.

## Build

### Linux

Using presets:
```bash
cmake --preset linux-debug
cmake --build build/linux-debug --parallel
ctest --test-dir build/linux-debug --output-on-failure
```

SLES 15 SP7 with GCC 14:
```bash
rm -rf build/linux-release
cmake --preset linux-release-sles
cmake --build build/linux-release-sles --parallel
```

Artifacts:
* Standalone: `build/linux-release-sles/GovSynthModel1_artefacts/Release/Standalone/GovSynthModel1`
* VST3: `build/linux-release-sles/GovSynthModel1_artefacts/Release/VST3/GovSynthModel1.vst3`

The `linux-release-sles` preset sets `CMAKE_CXX_COMPILER=/usr/bin/g++-14` and `CMAKE_C_COMPILER=/usr/bin/gcc-14`.

### Windows

Prerequisites: Visual Studio 2022 with C++ workload, CMake 3.22+, Ninja.
Use Windows Developer PowerShell for native toolchain detection.

Using built-in preset:
```powershell
# Windows Developer PowerShell
cmake --preset windows-release
cmake --build build/windows-release --config Release
ctest --test-dir build/windows-release --output-on-failure
```

Recommended VS2022 user preset:
```powershell
# Windows Developer PowerShell
Remove-Item -Recurse -Force build
Copy-Item CMakeUserPresets.json.example CMakeUserPresets.json
cmake --preset windows-release-vs2022
cmake --build build/windows-release-vs2022 --config Release
```

Artifacts:
* Standalone: `build/windows-release-vs2022/GovSynthModel1_artefacts/Release/Standalone/GovSynthModel1.exe`
* VST3: `build/windows-release-vs2022/GovSynthModel1_artefacts/Release/VST3/GovSynthModel1.vst3`

Copy the entire `GovSynthModel1.vst3` folder to your VST3 path and rescan in your DAW.

## Testing

* Build succeeds with no warnings as errors
* Load VST3 in a DAW and verify MIDI note on/off produces sound
* Standalone launches and exposes parameters
* State save/restore works via APVTS

## Project Structure

See AGENTS.md for full architecture.

## License

See LICENSE

