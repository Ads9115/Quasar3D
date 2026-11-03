add_executable(testbed main.cpp)
target_link_libraries(testbed PRIVATE qs_physics qs_core)

add_executable(exp_variable_dt exp_variable_dt.cpp)
target_link_libraries(exp_variable_dt PRIVATE qs_core)

