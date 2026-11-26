# Building GovSynthModel1

This document describes how to build GovSynthModel1 on SUSE Linux Enterprise Server 15 SP7 and Windows 10/11 with Visual Studio 2022.

## Prerequisites

### General
* CMake 3.22+
* Ninja
* C++20 capable compiler: GCC 14+, Clang 14+, MSVC 2022
* JUCE 8.x as submodule

### SLES 15 SP7

Default GCC 7.5 does not support C++20. Install GCC 14 and dependencies:

```bash
sudo zypper refresh
sudo zypper install cmake ninja gcc14 gcc14-c++ libstdc++6-devel-gcc14 \
  pkg-config libX11-devel libXext-devel libXinerama-devel libXcursor-devel libXtst-devel \
  freetype2-devel fontconfig-devel Mesa-libGL-devel alsa-devel libjack-devel
```

Verify:
```bash
g++-14 --version
```

The `linux-release-sles` preset forces `CMAKE_CXX_COMPILER=/usr/bin/g++-14` and `CMAKE_C_COMPILER=/usr/bin/gcc-14`.

### Windows

* Visual Studio 2022 with "Desktop development with C++" workload
* CMake 3.22+
* Ninja
* Use **Windows Developer PowerShell** for native MSVC detection

## Build Steps

### Linux SLES

```bash
cmake --preset linux-release-sles
cmake --build build/linux-release-sles
```

Artifacts:
* Standalone: `build/linux-release-sles/GovSynthModel1_artefacts/Release/Standalone/GovSynthModel1`
* VST3: `build/linux-release-sles/GovSynthModel1_artefacts/Release/VST3/GovSynthModel1.vst3`

### Windows

Copy user presets first:
```powershell
Copy-Item CMakeUserPresets.json.example CMakeUserPresets.json
```

Build with VS2022:
```powershell
# Windows Developer PowerShell
cmake --preset windows-release-vs2022
cmake --build build/windows-release-vs2022 --config Release
ctest --test-dir build/windows-release-vs2022 --output-on-failure
```

Artifacts:
* Standalone: `build/windows-release-vs2022/GovSynthModel1_artefacts/Release/Standalone/GovSynthModel1.exe`
* VST3: `build/windows-release-vs2022/GovSynthModel1_artefacts/Release/VST3/GovSynthModel1.vst3`

Copy the entire `GovSynthModel1.vst3` folder to your VST3 path and rescan in your DAW.

## Troubleshooting

### SLES: CMake error "Target requires language dialect CXX20"

Cause: Default `g++` is 7.5 which lacks C++20 support.

Fix: Use the `linux-release-sles` preset which forces `g++-14`. Do not use generic `linux-release`.

### SLES: Package not found `libasound2-devel`

SLES uses `alsa-devel` instead of `libasound2-devel`.

Fix:
```bash
sudo zypper install alsa-devel
```

### Windows: MSVC not found

Cause: Running in regular PowerShell, not Windows Developer PowerShell.

Fix: Open "Windows Developer PowerShell" from Start Menu. Verify with:
```powershell
cmake --version
cl.exe
```

### Windows: VST3 not loading in DAW

Cause: Wrong architecture or product name with spaces.

Fix: Build with `windows-release-vs2022` preset which uses Visual Studio 17 2022 generator x64 and product name `GovSynthModel1`. Copy the whole `.vst3` bundle, not just the `.vst3` file inside.

### General: JUCE submodule missing

```bash
git submodule update --init --recursive
```

## Testing

* Build succeeds with no warnings as errors
* Standalone launches and responds to MIDI
* VST3 loads in host, parameters are automatable
* State save/restore works via APVTS

## VST3 Installation Paths

Copy the entire `GovSynthModel1.vst3` folder, not just the inner `.so`/`.vst3` file.

### Windows
Standard user VST3 path:
`%USERPROFILE%\Documents\VST3\GovSynthModel1.vst3`

Rescan plugins in your DAW after copying.

### Linux
Standard user VST3 path:
`~/.vst3/GovSynthModel1.vst3`

Or system wide:
`/usr/local/lib/vst3/GovSynthModel1.vst3`

Ensure the folder contains `Contents/x86_64-linux/GovSynthModel1.so` and `Contents/Resources/moduleinfo.json`.
