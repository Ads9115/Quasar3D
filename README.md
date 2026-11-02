# Quasar3D

> A modular 3D physics engine in C++.

![License](https://img.shields.io/badge/License-Apache%202.0-blue)
![Status](https://img.shields.io/badge/Status-In%20Development-orange)
![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C)

Quasar3D is an open-source, modular 3D physics engine project written in C++. It aims to provide a clear, reusable foundation for simulation in games and other real-time applications. Its modular design lets math, shared utilities, and physics evolve independently while remaining easy to combine in applications such as the included testbed. The project is in early development, and its APIs and capabilities will grow and change over time.

## Architecture

Quasar3D is organized into separate Core, Math, and Physics modules. Core provides shared utilities, Math supplies common GLM-based types and helpers, and Physics uses them to represent and advance simulation worlds. The console testbed is an application built on these modules, while tests check the simulation and math conventions. This separation lets the physics functionality develop independently from applications that use it.

## Build

Requirements: CMake 3.10 or newer, a C++17 compiler, and Git. CMake fetches the project's build dependencies during configuration, so network access is needed the first time.

```bash
cmake -S . -B build
cmake --build build
./build/apps/testbed/testbed
```

Run the tests with:

```bash
ctest --test-dir build --output-on-failure
```

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE) for details.
