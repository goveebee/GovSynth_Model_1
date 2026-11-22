# Emil Synth --- OpenCode Agent Instructions

> **Project:** Emil Synth\
> **Type:** Classic analog-inspired polyphonic synthesizer\
> **Primary format:** VST3\
> **Development host:** Separate x86-64 Linux workstation\
> **Target platforms:** Linux and Windows (64-bit)\
> **Framework:** JUCE\
> **Language:** C++20\
> **Build:** CMake + Ninja\
> **IDE/agent:** VS Code + OpenCode\
> **Status:** Initial implementation / MVP

This file is the persistent working agreement for OpenCode and other
coding agents operating in this repository. Follow it before changing
code. If repository reality differs from this document, inspect the code
and build configuration, explain the discrepancy, and update this
document when the architecture changes.

------------------------------------------------------------------------

## 1. Product goal

Build a reliable, low-latency, polyphonic, classic analog-style
synthesizer that loads as a VST3 instrument in a DAW.

The first deliverable is a working MVP that:

1.  Builds as a Linux VST3 and standalone application.
2.  Has a Windows VST3 build from the same source tree.
3.  Receives MIDI note-on, note-off, velocity, pitch bend, and
    modulation wheel.
4.  Produces sound using two oscillators per voice.
5.  Provides saw, square/pulse, triangle, and sine waveforms.
6.  Has a resonant low-pass filter and an amplitude ADSR.
7.  Exposes all user-controllable parameters to DAW automation.
8.  Saves and restores plugin state.
9.  Has a simple, usable hardware-inspired GUI.
10. Can be tested without a DAW using the standalone target and
    automated unit tests where practical.

The initial sound should be warm and musical, with useful bass, lead,
and pad sounds. Do not claim that the sound is a perfect analog circuit
emulation. Prioritize stability, musicality, and predictable controls.

### Non-goals for MVP

-   AI-generated sounds or presets.
-   Sample playback engine.
-   Wavetable editor.
-   Built-in arpeggiator or sequencer.
-   Browser, network, cloud, or account integration.
-   Copying the design, artwork, presets, or trademarks of an existing
    synthesizer.
-   Installer/signing/distribution automation beyond basic build
    artifacts.

Keep the architecture extensible so these features can be added later
without compromising the audio thread.

------------------------------------------------------------------------

## 2. Target platforms and portability

### Supported targets

-   Linux x86-64: VST3 and standalone.
-   Windows x86-64: VST3 and standalone.
-   macOS is not currently a target. Avoid unnecessary platform-specific
    assumptions that would prevent a future port.

### Cross-platform rules

-   Use JUCE abstractions for audio devices, MIDI, GUI, files, and
    plugin hosting.
-   Do not hard-code Linux paths, Windows paths, device names, or
    DAW-specific behavior in the synth engine.
-   Use `std::filesystem` or JUCE file APIs for filesystem operations.
-   Use UTF-8 for project text and preset metadata.
-   Use CMake generator expressions and platform checks rather than
    shell-specific build logic in CMake.
-   Keep platform-specific code isolated and justified.
-   Never assume Linux VST3 binaries can run on Windows or vice versa.
    Build each target on its native toolchain or a properly configured
    cross-build environment.
-   Prefer native Windows CI/builds (for example, a Windows runner) for
    the Windows release. Cross-compilation from Linux may be
    investigated later, but is not the initial supported release path.

### Linux distribution is not yet specified

The development machine is a separate Linux workstation, but the
distribution is currently unknown. Do not assume Ubuntu, Debian, Fedora,
Arch, or openSUSE.

Before giving exact package commands, inspect `/etc/os-release` or ask
the user which distribution and version is installed. Provide package
names for the detected distribution. Do not run privileged package
installation commands without explicit user approval.

The project itself must remain distribution-neutral. Use documented
system packages for JUCE's Linux dependencies and audio backend
development headers.

------------------------------------------------------------------------

## 3. Technical decisions

### Core stack

-   C++20.
-   JUCE (pin to a known stable release or commit; do not track `master`
    in production builds).
-   CMake 3.22 or newer, unless the pinned JUCE release requires a newer
    version.
-   Ninja recommended; Unix Makefiles are acceptable.
-   GCC or Clang on Linux.
-   MSVC on Windows.
-   CTest for test discovery and execution.
-   Git with JUCE as a pinned submodule.

### JUCE usage

-   Use JUCE's CMake integration (`add_subdirectory(JUCE)` and
    `juce_add_plugin`).
-   Use `juce::AudioProcessorValueTreeState` (APVTS) for host-visible
    parameters and state.
-   Use JUCE's plugin and DSP abstractions where they provide clear
    value.
-   A custom DSP implementation is acceptable for oscillators and filter
    behavior, provided it is tested and documented.
-   Prefer JUCE's `Synthesiser`, `SynthesiserVoice`, and
    `SynthesiserSound` for initial voice management unless a measured
    requirement justifies a custom allocator.
-   Do not create a custom VST3 SDK integration unless JUCE's supported
    integration cannot meet a documented requirement.

### Plugin formats

Initial plugin formats: - `VST3` - `Standalone`

The plugin is an instrument: - `IS_SYNTH TRUE` -
`NEEDS_MIDI_INPUT TRUE` - `NEEDS_MIDI_OUTPUT FALSE`

Do not add AU/AAX/LV2 formats unless explicitly requested and
licensing/build requirements are reviewed.

### JUCE dependency policy

-   Add JUCE as a Git submodule under `JUCE/`.
-   Pin the submodule to a stable tag or commit.
-   Commit the submodule pointer, not JUCE's full source tree.
-   Record the exact JUCE version/commit in `README.md`.
-   Avoid changing JUCE version and application code in the same change
    unless necessary.
-   Review JUCE licensing before public or commercial distribution. Do
    not assume that development use and commercial distribution have
    identical requirements.

------------------------------------------------------------------------

## 4. Repository structure

Use this structure as the intended layout. It is acceptable to introduce
a new file when it has a clear responsibility. Avoid empty placeholder
files and avoid creating abstractions that are not used.

``` text
EmilSynth/
├── AGENTS.md
├── README.md
├── LICENSE
├── .gitignore
├── .gitmodules
├── CMakeLists.txt
├── CMakePresets.json
├── cmake/
│   ├── CompilerWarnings.cmake
│   └── Sanitizers.cmake
├── JUCE/                         # pinned Git submodule
├── Source/
│   ├── Plugin/
│   │   ├── PluginProcessor.h
│   │   ├── PluginProcessor.cpp
│   │   ├── PluginEditor.h
│   │   └── PluginEditor.cpp
│   ├── Parameters/
│   │   ├── ParameterIDs.h
│   │   ├── ParameterLayout.h
│   │   └── ParameterLayout.cpp
│   ├── Engine/
│   │   ├── SynthEngine.h
│   │   ├── SynthEngine.cpp
│   │   ├── SynthVoice.h
│   │   ├── SynthVoice.cpp
│   │   ├── SynthSound.h
│   │   └── SynthSound.cpp
│   ├── DSP/
│   │   ├── Oscillator.h
│   │   ├── Oscillator.cpp
│   │   ├── Envelope.h
│   │   ├── Envelope.cpp
│   │   ├── Filter.h
│   │   ├── Filter.cpp
│   │   ├── LFO.h
│   │   ├── LFO.cpp
│   │   └── Smoothing.h
│   ├── UI/
│   │   ├── SynthLookAndFeel.h
│   │   ├── SynthLookAndFeel.cpp
│   │   ├── MainPanel.h
│   │   ├── MainPanel.cpp
│   │   ├── OscillatorPanel.h
│   │   ├── OscillatorPanel.cpp
│   │   ├── FilterPanel.h
│   │   ├── FilterPanel.cpp
│   │   ├── EnvelopePanel.h
│   │   └── EnvelopePanel.cpp
│   └── Utility/
│       ├── Constants.h
│       └── DenormalGuard.h
├── Tests/
│   ├── CMakeLists.txt
│   ├── TestMain.cpp
│   ├── OscillatorTests.cpp
│   ├── EnvelopeTests.cpp
│   ├── FilterTests.cpp
│   └── ParameterTests.cpp
├── Presets/
│   ├── Factory/
│   │   └── Init.emsynth
│   └── User/
│       └── .gitkeep
├── Resources/
│   ├── Fonts/
│   └── Images/
├── docs/
│   ├── ARCHITECTURE.md
│   ├── DSP_NOTES.md
│   ├── BUILDING.md
│   └── ROADMAP.md
└── build/                         # ignored; generated locally
```

### Ownership boundaries

-   `Plugin/`: JUCE host-facing integration only.
-   `Parameters/`: canonical parameter IDs, ranges, defaults, units, and
    APVTS layout.
-   `Engine/`: voice allocation and per-voice signal flow.
-   `DSP/`: reusable audio algorithms independent of GUI.
-   `UI/`: controls and presentation; no audio generation.
-   `Tests/`: deterministic tests for DSP and parameter behavior.
-   `Presets/`: factory presets and user preset format.
-   `docs/`: design decisions and developer documentation.

Do not let DSP classes depend on GUI classes. Avoid making DSP classes
depend directly on `AudioProcessor` or APVTS. Pass parameter values into
the engine through a clearly defined, real-time-safe interface.

------------------------------------------------------------------------

## 5. Synthesizer specification

### MVP signal path

``` text
MIDI
  |
  v
Voice allocation (initially 8 voices; configurable up to 16)
  |
  +--> Oscillator 1 --\
  |                   +--> Oscillator mixer --> Low-pass filter --> Amp envelope
  +--> Oscillator 2 --/                                      |
                                                             v
                                                        Master gain
                                                             |
                                                             v
                                                        Stereo output
```

MVP voice count: - Start with 8 voices to simplify validation. - Make
the voice limit configurable at compile-time or through a controlled
engine setting. - Raise the default to 16 after CPU and voice-stealing
tests pass. - Voice stealing must be deterministic and must not allocate
memory in the audio callback.

### Oscillators

Two oscillators per voice.

Waveforms: - Sine. - Triangle. - Saw. - Square/pulse.

Controls: - Waveform. - Octave. - Semitone. - Fine tune/detune. -
Level. - Oscillator 2 pulse width may be added after the basic waveforms
work.

Requirements: - Avoid naive discontinuous saw and square generation at
high frequencies. - Use a band-limited method such as PolyBLEP or
precomputed band-limited wavetables. - Document the chosen method and
its limitations. - Handle sample-rate changes correctly. - Avoid clicks
on note start/stop and waveform changes. - Phase and frequency must
remain finite and stable. - Add tests for frequency, waveform range,
silence, and aliasing-oriented behavior where practical.

### Mixer

-   Independent oscillator levels.
-   Prevent accidental clipping through sensible gain staging.
-   Do not normalize each voice independently in a way that causes
    unstable perceived loudness.
-   Document whether oscillator levels are linear or decibel-scaled.

### Filter

MVP: - Resonant low-pass filter. - Target slope/character: 24 dB/octave,
ladder-inspired. - Cutoff and resonance parameters. - Optional
filter-envelope amount after base filter is stable.

Requirements: - Stable at supported sample rates and high resonance. -
No NaN/Inf output for valid parameter ranges. - Smooth cutoff/resonance
changes. - Test impulse response, frequency response, stability, and
resonance extremes. - Do not claim exact analog modeling unless measured
and justified. - A well-tested JUCE DSP filter is acceptable for the
first milestone if it provides a stable result. A custom ladder model
can replace it in a later, isolated change.

### Envelopes

MVP: - Amp ADSR.

Next: - Filter ADSR.

Controls: - Attack. - Decay. - Sustain. - Release.

Requirements: - Time values must be musically useful and have safe
bounds. - Parameter changes must not create discontinuities. - Note-off
must trigger release correctly. - Retrigger behavior must be
documented. - Test zero/very short and maximum times.

### LFO and modulation

After MVP: - LFO 1 and LFO 2. - Sine, triangle, saw, square as useful. -
Rate and depth. - Destinations initially: pitch and filter cutoff. - Mod
wheel controls a documented modulation amount. - Keep modulation routing
simple until the core synth is stable.

### Effects

After core synthesis: - Chorus. - Delay. - Optional stereo width.

Effects must be implemented with bounded memory and real-time-safe
processing. Do not add convolution or expensive neural effects to the
audio callback.

------------------------------------------------------------------------

## 6. Parameter and state contract

Use APVTS for host automation and plugin state.

Rules: 1. Every automatable parameter has a stable, unique string ID. 2.
Never rename or reuse a released parameter ID without a migration plan.
3. Parameter ranges, defaults, units, and skew must be documented. 4.
Use appropriate JUCE parameter types (`AudioParameterFloat`,
`AudioParameterChoice`, `AudioParameterBool`, etc.). 5. GUI controls
must attach to APVTS parameters; do not maintain a second independent
value. 6. DSP reads parameter values using a real-time-safe approach. 7.
Do not access GUI components from the audio thread. 8. Save/restore
APVTS state through the plugin state methods. 9. Test save/restore and
default-state behavior.

Initial stable parameter IDs (extend consistently):

``` text
osc1_wave
osc1_octave
osc1_semitone
osc1_detune
osc1_level

osc2_wave
osc2_octave
osc2_semitone
osc2_detune
osc2_level

filter_cutoff
filter_resonance
filter_env_amount

amp_attack
amp_decay
amp_sustain
amp_release

filter_attack
filter_decay
filter_sustain
filter_release

lfo1_rate
lfo1_depth
lfo1_destination

master_volume
polyphony
```

Do not expose parameters that have no working DSP implementation. It is
better to add parameters in the milestone that implements them.

------------------------------------------------------------------------

## 7. Real-time audio rules (mandatory)

The audio callback and all functions reachable from it must be real-time
safe.

Never do the following in the audio thread: - Heap
allocation/deallocation (`new`, `delete`, growing containers, string
construction). - File I/O or preset loading. - Network access. -
Logging, console output, or blocking diagnostics. - Mutex locking or
waiting on condition variables. - GUI updates or component access. -
Creating/destroying DSP objects. - Unbounded loops or unpredictable
work.

Required practices: - Allocate and prepare DSP state in
`prepareToPlay`. - Release resources in `releaseResources`. - Handle
arbitrary host block sizes. - Handle mono and stereo layouts supported
by the plugin. - Handle sample-rate changes. - Smooth parameters that
can cause discontinuities. - Use denormal protection where
appropriate. - Clear output buffers before writing when required. -
Process MIDI events in sample order and handle multiple events in a
block. - Avoid assumptions that one MIDI event occurs per audio block. -
Do not assume fixed sample rate or fixed buffer size. - Keep CPU use
bounded at the maximum voice count. - Add comments for non-obvious
real-time constraints.

If cross-thread communication is needed, use atomics for simple scalar
values or a suitable lock-free/bounded queue. Do not invent a lock-free
structure without tests and a clear need.

------------------------------------------------------------------------

## 8. GUI and UX requirements

Visual direction: - Hardware-inspired classic analog synthesizer. - Dark
charcoal or muted metal panel. - Warm cream/amber labels. - Large,
readable knobs. - Clear oscillator, filter, envelope, LFO, and effects
sections. - No imitation of a specific commercial synth's exact panel or
branding.

Initial editor: - Resizable if practical; otherwise use a sensible fixed
initial size. - Logical grouping and consistent knob sizes. - Show
parameter values and units. - Controls must be accessible and usable at
typical desktop scaling. - Avoid excessive decoration that reduces
readability. - GUI must not perform audio processing.

Implement a custom `LookAndFeel` only where it improves consistency.
Keep components small and focused. Prefer reusable controls over
duplicated drawing code.

------------------------------------------------------------------------

## 9. Presets

MVP: - An Init preset. - A small set of factory presets after the sound
engine is stable.

Preset requirements: - Store parameter state, not rendered audio. -
Include a schema/version field. - Validate data when loading. - Loading
must not perform file I/O on the audio thread. - Use a safe handoff to
apply parameter changes. - User presets must be stored in the user's
platform-appropriate application data directory. - Do not assume the
current working directory is the plugin's installation directory.

Suggested initial factory categories: - Bass. - Lead. - Pad. - Pluck. -
FX (later).

Use an extension such as `.emsynth` and a documented serialization
format. XML or JSON is acceptable; choose one and keep it versioned. Do
not create a custom binary format without a compelling reason.

------------------------------------------------------------------------

## 10. Build and development workflow

### Linux host

The exact package names depend on the Linux distribution.

Before installation: 1. Inspect `/etc/os-release`. 2. Identify the
package manager. 3. Check the installed compiler and CMake versions. 4.
Install JUCE's Linux build dependencies for the pinned JUCE release. 5.
Install an audio backend suitable for testing (PipeWire/JACK/ALSA as
appropriate). 6. Do not assume that installing a runtime audio server
also installs its development headers.

Typical tools: - Git. - CMake. - Ninja. - GCC or Clang with C++20
support. - pkg-config. - X11 development libraries or the relevant
supported display backend. - ALSA/JACK/PipeWire development packages as
required by the JUCE configuration. - FreeType and fontconfig
development packages. - OpenGL development libraries where required.

Do not blindly copy Ubuntu package lists to Fedora, Arch, openSUSE, or
another distribution. Consult the distribution's package manager and
JUCE's current Linux build documentation.

### Initial repository setup

``` bash
git clone --recurse-submodules <repository-url>
cd EmilSynth

# If the repository was cloned without submodules:
git submodule update --init --recursive

cmake --version
c++ --version
ninja --version
```

### Configure and build

``` bash
cmake -S . -B build/linux-debug \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug

cmake --build build/linux-debug
```

Release build:

``` bash
cmake -S . -B build/linux-release \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build/linux-release
```

Run tests:

``` bash
ctest --test-dir build/linux-debug --output-on-failure
```

The exact artifact directory is determined by JUCE/CMake and the
configured plugin target. Do not hard-code an assumed path in scripts;
inspect the build output or use CMake target properties.

### Windows build

The supported release path is a native Windows build using: - Windows
10/11 x64. - Visual Studio 2022 (MSVC C++ workload). - CMake. - Ninja or
Visual Studio generator. - Same repository and pinned JUCE submodule.

Example from a Windows Developer PowerShell:

``` powershell
cmake -S . -B build/windows-release -G Ninja `
  -DCMAKE_BUILD_TYPE=Release

cmake --build build/windows-release
ctest --test-dir build/windows-release --output-on-failure
```

Do not promise a Windows artifact from a Linux build. If Windows build
automation is added, use a Windows CI runner and keep its commands
documented.

### CMake presets

Provide presets for Linux Debug/Release. Windows presets may be included
if they work with the selected generator and toolchain. Do not make a
preset silently assume a particular absolute path or local compiler
installation.

------------------------------------------------------------------------

## 11. Testing and quality gates

Every meaningful DSP feature must have tests.

Minimum test coverage: - Oscillator generates finite output. -
Oscillator frequency is within tolerance. - Oscillator output stays
within documented bounds. - ADSR reaches attack, decay, sustain, and
release stages correctly. - Filter remains finite and stable at
cutoff/resonance extremes. - Parameter defaults match documentation. -
State save/restore preserves parameter values. - MIDI note-on creates
sound. - MIDI note-off releases the voice. - Voice stealing does not
leave stuck notes. - Plugin can prepare and process at common sample
rates (44.1, 48, 88.2, 96 kHz). - Mono/stereo handling is intentional
and tested.

Use Debug builds during development. Add sanitizers where supported: -
AddressSanitizer. - UndefinedBehaviorSanitizer. - ThreadSanitizer for
suitable non-real-time tests; do not assume it can be used meaningfully
in every DAW/plugin-host scenario.

Before declaring a milestone complete: 1. Build from a clean build
directory. 2. Run all tests. 3. Test standalone where relevant. 4. Test
plugin loading in at least one Linux VST3 host. 5. For Windows changes,
run a native Windows build and host test before release. 6. Report any
untested platform explicitly.

Do not claim tests passed unless they were actually run and their output
checked.

------------------------------------------------------------------------

## 12. Coding standards

-   Use modern C++20, but avoid clever abstractions.
-   Prefer RAII and value semantics.
-   Use `const` where appropriate.
-   Keep functions small and responsibilities clear.
-   Avoid raw owning pointers.
-   Use `std::unique_ptr` for ownership when needed.
-   Avoid unnecessary inheritance.
-   Use `enum class` for enumerations.
-   Use descriptive names and consistent formatting.
-   Do not introduce third-party dependencies without explaining why.
-   Do not add a dependency merely to avoid a small, clear
    implementation.
-   Do not suppress compiler warnings globally.
-   Fix warnings introduced by the change.
-   Document units (Hz, seconds, dB, semitones, normalized values).
-   Use explicit conversions where numeric types differ.
-   Avoid magic numbers; put meaningful constants in named definitions.
-   Keep public headers minimal.
-   Do not put implementation-heavy code in headers unless justified.

Use a consistent formatting style. If a `.clang-format` file is added,
apply it consistently and do not reformat unrelated files.

------------------------------------------------------------------------

## 13. OpenCode agent operating procedure

Before starting a task: 1. Read this `AGENTS.md`. 2. Read `README.md`
and relevant architecture/DSP documents. 3. Inspect the actual source
tree and current Git status. 4. Identify the smallest useful change. 5.
State assumptions if requirements are unclear.

When implementing: 1. Make focused changes. 2. Preserve the existing
architecture unless there is a concrete reason to change it. 3. Do not
rewrite unrelated files. 4. Do not change parameter IDs casually. 5. Do
not add placeholder implementations that appear complete but do nothing.
6. Keep DSP independent from GUI and host integration. 7. Ensure
real-time audio rules are respected. 8. Update tests and documentation
with behavior changes.

After implementing: 1. Configure/build the affected target. 2. Run
relevant tests. 3. Inspect `git diff`. 4. Report files changed, design
decisions, commands run, and actual results. 5. List anything not
tested, especially platform-specific behavior.

### Approval boundaries

Ask before: - Installing system packages or changing system
configuration. - Running commands with `sudo`. - Changing the JUCE
submodule version. - Adding a third-party library. - Changing the plugin
identity/manufacturer/plugin codes after the first release. - Changing
the preset/state format. - Introducing network access or AI services. -
Removing user data or presets. - Making a breaking change to parameter
IDs or serialized state.

Do not: - Commit, push, publish, or release unless explicitly asked. -
Claim that a plugin was tested in a DAW unless it was. - Guess the
user's Linux distribution. - Modify files outside the repository unless
explicitly required. - Include secrets, credentials, or personal paths
in source control.

------------------------------------------------------------------------

## 14. Milestones and acceptance criteria

### M0 --- Repository and build skeleton

Deliver: - JUCE pinned as submodule. - CMake project. - Linux VST3 and
standalone targets. - Windows-compatible project configuration. - README
with setup instructions. - A clean build on Linux.

Acceptance: - Configure and compile successfully on the Linux
workstation. - Plugin artifact is produced. - No machine-specific
absolute paths in tracked files.

### M1 --- First audible instrument

Deliver: - MIDI input. - One oscillator. - One voice. - Amp envelope. -
Master gain. - Minimal GUI or a basic level/control panel.

Acceptance: - Load in a Linux VST3 host. - Play MIDI notes and hear
sound. - Note-off releases the sound. - No obvious clicks or stuck notes
in basic use.

### M2 --- Dual oscillator and polyphony

Deliver: - Two oscillators per voice. - Four waveforms. - Oscillator
levels and tuning. - 8 voices, then 16 after profiling. - Voice
stealing.

Acceptance: - Play chords. - Change waveforms and tuning. - CPU remains
reasonable. - No stuck notes after dense MIDI input.

### M3 --- Filter and envelopes

Deliver: - Resonant low-pass filter. - Amp ADSR. - Filter ADSR and
modulation amount. - Parameter smoothing.

Acceptance: - Filter behaves musically. - Extreme settings remain
stable. - Parameters automate in the host.

### M4 --- Modulation and effects

Deliver: - Two LFOs. - Pitch/filter modulation. - Chorus and delay.

Acceptance: - Modulation is repeatable and stable. - Effects do not
create unbounded CPU or memory use. - Bypass and parameter changes are
click-free where practical.

### M5 --- GUI, presets, and state

Deliver: - Hardware-inspired GUI. - Preset browser. - Factory presets. -
User preset save/load. - APVTS state serialization.

Acceptance: - DAW project reload restores the instrument state. -
Presets load safely. - GUI and automation remain synchronized.

### M6 --- Cross-platform release

Deliver: - Linux VST3 and standalone release. - Windows VST3 and
standalone release. - Build instructions for both. - Versioned release
notes.

Acceptance: - Native Linux build and host test pass. - Native Windows
build and host test pass. - No platform-specific regressions known to
the team. - Licensing and distribution requirements reviewed.

------------------------------------------------------------------------

## 15. Definition of done

A task is done only when: - The implementation matches the requested
behavior. - The code compiles for the relevant target. - Relevant tests
pass. - Real-time constraints are respected. - No unrelated changes are
included. - Documentation is updated where needed. - The final response
accurately distinguishes tested behavior from assumptions.

The MVP is complete when Emil Synth can be loaded as a VST3 instrument
in a Linux DAW, receive MIDI, play a stable dual-oscillator polyphonic
sound with filter and amp envelope, expose automatable parameters, and
save/restore its state. A Windows build must be demonstrated separately
before claiming Windows support.

------------------------------------------------------------------------

## 16. First task for the coding agent

When this repository is first opened, do not immediately implement the
entire synthesizer.

Start with this sequence:

1.  Inspect the Linux distribution using `/etc/os-release` and report
    it.
2.  Check installed compiler, CMake, Ninja, Git, and required
    development packages.
3.  Do not install packages automatically. Report missing packages and
    ask before using `sudo`.
4.  Create or verify the repository structure.
5.  Add JUCE as a submodule and pin it to a stable release.
6.  Create the smallest valid CMake project producing VST3 and
    standalone targets.
7.  Add a minimal `AudioProcessor` and editor using JUCE's generated
    plugin structure.
8.  Configure and build Debug.
9.  Run available tests.
10. Document exact build commands and artifact locations in `README.md`
    and `docs/BUILDING.md`.

Only after M0 is verified should the agent begin M1.

**First user-visible report:** detected Linux distribution,
compiler/CMake versions, missing dependencies, files created, build
result, and the next recommended action.
