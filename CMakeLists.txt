cmake_minimum_required(VERSION 4.1)
project(cpu_impl)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.12.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(cpu_impl src/main.cpp
        src/cpu.cpp
)

add_executable(cpu_impl_tests tests/test.cpp
        src/cpu.cpp
)
target_link_libraries(cpu_impl_tests PRIVATE Catch2::Catch2WithMain)
