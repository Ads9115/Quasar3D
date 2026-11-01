cmake_minimum_required(VERSION 3.10)
project(Quasar3D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1)        # pinned: this exact version, forever
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2)
FetchContent_MakeAvailable(glm Catch2)

add_subdirectory(modules/core)
add_subdirectory(modules/math)
add_subdirectory(modules/physics)
add_subdirectory(apps/testbed)

enable_testing()
add_subdirectory(tests)

