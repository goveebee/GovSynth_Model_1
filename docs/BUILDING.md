# Building

## Linux

```bash
cmake -S . -B build/linux-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/linux-debug
```

## Windows

```bash
cmake -S . -B build/windows-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/windows-release
```
