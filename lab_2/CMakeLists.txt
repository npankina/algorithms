cmake_minimum_required(VERSION 3.26)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)

# Установка пути к библиотеке Boost
#set(BOOST_ROOT "/opt/local/include")
#find_package(Boost 1.76.0) #  REQUIRED algorithm

add_executable(app main.cpp Array/Array.cpp List/List.cpp)
#target_link_libraries(app PRIVATE Boost::headers ) # Boost::algorithm

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(Tests
        Test/testing_for_containers.cpp
        Array/Array.cpp
        List/List.cpp
        Data/Subcriber.cpp
        Data/Record.cpp)


target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(Tests)
enable_testing()