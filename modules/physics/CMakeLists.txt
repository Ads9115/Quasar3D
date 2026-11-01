add_library(qs_physics STATIC src/world.cpp)
target_include_directories(qs_physics PUBLIC include)
target_link_libraries(qs_physics PUBLIC qs_math qs_core)
target_compile_options(qs_physics PRIVATE -Wall -Wextra)
