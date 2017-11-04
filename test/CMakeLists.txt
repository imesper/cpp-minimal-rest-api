set(TEST_EXECUTABLE run_rest_api_test)
set(TEST_SOURCE rest_api_test.cpp)


add_executable(${TEST_EXECUTABLE} ${TEST_SOURCE})

target_link_libraries(${TEST_EXECUTABLE} gtest gtest_main ${PROJECT_NAME} cpprest boost_system ssl1 crypto1)

add_test(rest_api_test ${TEST_EXECUTABLE})

install(
    TARGETS
    ${TEST_EXECUTABLE}
    CONFIGURATIONS
    Debug
    DESTINATION
    ${PROJECT_SOURCE_DIR}/bin/debug
)

install(
    TARGETS
    ${TEST_EXECUTABLE}
    CONFIGURATIONS
    Release
    DESTINATION
    ${PROJECT_SOURCE_DIR}/bin/release
)
