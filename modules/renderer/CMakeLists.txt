add_library(qs_renderer STATIC src/renderer.cpp)
target_include_directories(qs_renderer PUBLIC include)
target_link_libraries(qs_renderer PUBLIC qs_math qs_core qs_platform PRIVATE glad_gl)
target_compile_options(qs_renderer PRIVATE -Wall -Wextra)
