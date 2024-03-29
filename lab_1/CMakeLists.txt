cmake_minimum_required(VERSION 3.26)
project(lab_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_1 main.cpp)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests Test/test.cpp part_1/List.cpp part_1/Record.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(tests)
enable_testing()
