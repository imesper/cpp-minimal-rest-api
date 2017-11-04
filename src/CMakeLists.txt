
file (GLOB INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*h)

set(SOURCE_FILES
    BaseServiceServer
    PostsService.cpp
    ${INCLUDE_FILES}
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(run_${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} cpprest boost_system ssl1 crypto1)
target_link_libraries(run_${PROJECT_NAME} ${PROJECT_NAME})

install(
    TARGETS
    run_${PROJECT_NAME}
    CONFIGURATIONS
    Debug
    DESTINATION
    ${PROJECT_SOURCE_DIR}/bin/debug
)

install(
    TARGETS
    run_${PROJECT_NAME}
    CONFIGURATIONS
    Release
    DESTINATION
    ${PROJECT_SOURCE_DIR}/bin/release
)

install(
    TARGETS
    ${PROJECT_NAME}
    CONFIGURATIONS
    Debug
    DESTINATION
    ${PROJECT_SOURCE_DIR}/lib/debug
)

install(
    TARGETS
    ${PROJECT_NAME}
    CONFIGURATIONS
    Release
    DESTINATION
    ${PROJECT_SOURCE_DIR}/lib/release
)
