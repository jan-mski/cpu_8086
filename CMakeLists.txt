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

add_executable(cpu_impl_tests tests/test.cpp
        src/op_decoder/decoder.h
        src/op_decoder/decoder.cpp
        src/op_decoder/subdecoders/op_decoders.cpp
        src/types.h
        src/op_decoder/subdecoders/field_decoders.cpp
        src/op_decoder/subdecoders/subdecoders.h
        src/op_decoder/subdecoders/reg_mem_decoders.cpp
        src/op_decoder/subdecoders/operand_decoders.cpp)
target_link_libraries(cpu_impl_tests PRIVATE Catch2::Catch2WithMain)

add_executable(cpu_impl src/main.cpp
        src/op_decoder/decoder.h
        src/op_decoder/decoder.cpp
        src/op_decoder/subdecoders/op_decoders.cpp
        src/types.h
        src/op_decoder/subdecoders/field_decoders.cpp
        src/op_decoder/subdecoders/subdecoders.h
        src/op_decoder/subdecoders/reg_mem_decoders.cpp
        src/op_decoder/subdecoders/operand_decoders.cpp
)
