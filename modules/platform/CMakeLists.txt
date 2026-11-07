add_library(qs_platform STATIC src/window.cpp)
target_include_directories(qs_platform PUBLIC include)
target_link_libraries(qs_platform PUBLIC qs_core PRIVATE glfw)
target_compile_options(qs_platform PRIVATE -Wall -Wextra)
