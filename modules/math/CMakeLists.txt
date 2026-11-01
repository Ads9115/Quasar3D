add_library(qs_math INTERFACE)
target_include_directories(qs_math INTERFACE include)
target_link_libraries(qs_math INTERFACE glm::glm)
target_compile_definitions(qs_math INTERFACE GLM_FORCE_CTOR_INIT)
