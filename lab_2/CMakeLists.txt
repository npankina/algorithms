cmake_minimum_required(VERSION 3.26)
project(array)
project(list)

set(CMAKE_CXX_STANDARD 20)

add_executable(array Array/main.cpp
        Array/Data/Subcriber.h)
add_executable(list List/main.cpp)


Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests_array
        Array/testing_for_array.cpp
        Array/Array.cpp
        Array/Data/Subcriber.cpp
        Array/Data/Record.cpp)

add_executable(tests_list
        List/testing_for_list.cpp
        List/List.cpp)

target_link_libraries(tests_array PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests_list PRIVATE Catch2::Catch2WithMain)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(tests_array)
catch_discover_tests(tests_list)
enable_testing()