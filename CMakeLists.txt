cmake_minimum_required (VERSION 3.5)

#For VSCode Clang
SET (CMAKE_CXX_FLAGS_INIT                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
SET (CMAKE_AR      "/usr/bin/llvm-ar")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
SET (CMAKE_NM      "/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
SET (CMAKE_CXX_STANDARD 11)

project(minimal-rest-api)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory (src)

find_package(Boost COMPONENTS system REQUIRED)

find_package(GTest)

include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_subdirectory(test)
