# Emil Synth

Classic analog-inspired polyphonic synthesizer VST3.

## Status

Milestone M0 - Repository and build skeleton

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

```bash
cmake -S . -B build/linux-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/linux-debug
ctest --test-dir build/linux-debug --output-on-failure
```

## Project Structure

See AGENTS.md for full architecture.

## License

See LICENSE
