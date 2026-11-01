# Quasar3D

> A modular 3D physics engine, built to be reused.

![License](https://img.shields.io/badge/License-Apache%202.0-blue)
![Status](https://img.shields.io/badge/Status-In%20Development-orange)
![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C)

Quasar3D is a reusable, modular 3D physics engine written in C++. It is designed to be embedded in custom game engines and other real-time applications, with a built-in editor viewport for visualizing and debugging simulations.

This project is under active development. APIs and structure are subject to change.

## Overview

- Rigid body dynamics in 3D
- Strictly separated modules (core, physics, renderer, editor) for easier debugging and reuse
- Editor-style interface with a navigable 3D viewport and grid

## Architecture

The engine is split into independent modules that communicate through well-defined interfaces. The physics module has no dependency on rendering, so it can be used on its own.

```
Editor      ImGui interface and 3D viewport
   |
Renderer    Drawing and debug visualization
   |
Physics     Simulation, collision, and solvers
   |
Core        Shared utilities and application loop
```

| Module   | Responsibility                                      |
|----------|-----------------------------------------------------|
| Core     | Shared utilities, logging, and the main loop        |
| Physics  | Rigid body simulation, collision detection, solvers |
| Renderer | Rendering of scenes and physics debug views         |
| Editor   | Interface for inspecting and controlling simulation |

## Tech Stack

C++, GLM, OpenGL (Vulkan if required), Dear ImGui. Primary development on Linux.

## Building

Build instructions will be added once the project structure stabilizes.

## License

Licensed under the Apache License, Version 2.0. See the [LICENSE](LICENSE) file for details.
