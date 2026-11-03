add_executable(qs_tests physics_tests.cpp core_tests.cpp)
target_link_libraries(qs_tests PRIVATE qs_physics qs_core Catch2::Catch2WithMain)
add_test(NAME qs_tests COMMAND qs_tests)
