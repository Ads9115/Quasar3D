add_library(qs_core INTERFACE)
target_include_directories(qs_core INTERFACE include)
target_link_libraries(qs_core INTERFACE qs_math)
