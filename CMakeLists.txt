cmake_minimum_required(VERSION 4.1)
project(cpu_8086)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.12.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(cpu_8086 src/main.cpp)

add_executable(cpu_8086_tests tests/test_cpu.cpp)
target_link_libraries(cpu_8086_tests PRIVATE Catch2::Catch2WithMain)
