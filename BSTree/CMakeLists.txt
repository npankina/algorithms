cmake_minimum_required(VERSION 3.31)
project(BSTree)

set(CMAKE_CXX_STANDARD 20)

# Загрузка GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Добавим исполняемый файл для тестов
add_executable(tests
        main.cpp
        BSTree.cpp
        tests.cpp
)

# Линкуем с GTest
target_link_libraries(tests
        gtest_main
)

# Опционально: включаем тестирование в CTest
enable_testing()
add_test(NAME RunAllTests COMMAND tests)