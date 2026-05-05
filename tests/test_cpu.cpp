#define _CRT_SECURE_NO_WARNINGS

#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"
#include "../src/simulator.cpp"

namespace test_cpu
{
    using simulator::ExecuteInstructions;

    const U8 NASM_CMD_MAX_LEN = 32;
    const U16 FILE_PATH_MAX_LEN = 256;
    const U32 FILE_DATA_MAX_LEN = 262144;

    size_t ReadFileData(char* data,
                        FILE* file)
    {
        size_t file_size = fread(data, 1, FILE_DATA_MAX_LEN, file);
        data[file_size] = '\0';

        return file_size;
    }

    TEST_CASE("Instructions are decoded correctly")
    {
        const char* file_name = "instruction_decoding_001";

        char input_file_path[FILE_PATH_MAX_LEN];
        snprintf(input_file_path, FILE_PATH_MAX_LEN, "tests/resources/%s", file_name);

        char output_file_path[FILE_PATH_MAX_LEN];
        snprintf(output_file_path, FILE_PATH_MAX_LEN, "%s", "test.asm");

        char assembled_file_path[FILE_PATH_MAX_LEN];
        snprintf(assembled_file_path, FILE_PATH_MAX_LEN, "%s", "test.bin");

        FILE* output_file = fopen(output_file_path, "w");
        REQUIRE(output_file != NULL);

        fprintf(output_file, "bits 16\n");

        ExecuteInstructions(output_file, input_file_path, ProgramFlag_PrintAsmString);

        fclose(output_file);

        char nasm_cmd[NASM_CMD_MAX_LEN];
        snprintf(nasm_cmd, NASM_CMD_MAX_LEN, "nasm %s -o %s", output_file_path, assembled_file_path);
        system(nasm_cmd);

        FILE* assembled_file = fopen(assembled_file_path, "rb");
        REQUIRE(assembled_file != NULL);

        FILE* input_file = fopen(input_file_path, "rb");
        REQUIRE(input_file != NULL);

        char assembled_data[FILE_DATA_MAX_LEN];
        size_t assembled_file_size = ReadFileData(assembled_data, assembled_file);

        char input_data[FILE_DATA_MAX_LEN];
        size_t input_file_size = ReadFileData(input_data, input_file);

        bool match = (assembled_file_size == input_file_size) &&
                     (memcmp(assembled_data, input_data, assembled_file_size) == 0);

        output_file = fopen(output_file_path, "rb");
        REQUIRE(output_file != NULL);

        char output_data[FILE_DATA_MAX_LEN];
        ReadFileData(output_data, output_file);

        printf("\nOutput for file (match=%i) '%s':\n%s", match, file_name, output_data);
        fclose(output_file);

        fclose(assembled_file);
        fclose(input_file);

        REQUIRE(match);
    }

    TEST_CASE("Instructions are executed correctly")
    {
        const char* file_name = GENERATE(
            "instruction_execution_001_mov",
            "instruction_execution_002_arithmetic",
            "instruction_execution_003_logical",
            "instruction_execution_004_bitwise",
            "instruction_execution_005_loop",
            "instruction_execution_006_stack",
            "instruction_execution_007_lea",
            "print_8086");

        char input_file_path[FILE_PATH_MAX_LEN];
        snprintf(input_file_path, FILE_PATH_MAX_LEN, "tests/resources/%s", file_name);

        char output_file_path[FILE_PATH_MAX_LEN];
        snprintf(output_file_path, FILE_PATH_MAX_LEN, "%s", "test.txt");

        FILE* output_file = fopen(output_file_path, "wb");
        REQUIRE(output_file != NULL);

        char verification_file_path[FILE_PATH_MAX_LEN];
        snprintf(verification_file_path, FILE_PATH_MAX_LEN, "tests/resources/%s.txt", file_name);
        FILE* verification_file = fopen(verification_file_path, "r");
        REQUIRE(verification_file != NULL);

        ProgramFlags program_flags = ProgramFlag_Execute
                                     | ProgramFlag_PrintFinalState
                                     | ProgramFlag_PrintExecutionTrace;
        ExecuteInstructions(output_file, input_file_path, program_flags);

        fclose(output_file);

        output_file = fopen(output_file_path, "rb");
        REQUIRE(output_file != NULL);

        char output_data[FILE_DATA_MAX_LEN];
        size_t output_file_size = ReadFileData(output_data, output_file);

        char verification_data[FILE_DATA_MAX_LEN];
        size_t verification_file_size = ReadFileData(verification_data, verification_file);

        bool match = (output_file_size == verification_file_size) &&
                     (memcmp(output_data, verification_data, verification_file_size) == 0);

        printf("\nOutput for file (match=%i) '%s':\n%s", match, file_name, output_data);

        fclose(output_file);
        fclose(verification_file);

        REQUIRE(match);
    }
}
