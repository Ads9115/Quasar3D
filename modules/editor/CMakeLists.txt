add_library(qs_editor STATIC src/editor.cpp)
target_include_directories(qs_editor PUBLIC include)
target_link_libraries(qs_editor PUBLIC qs_platform qs_core PRIVATE imgui)
target_compile_options(qs_editor PRIVATE -Wall -Wextra)
