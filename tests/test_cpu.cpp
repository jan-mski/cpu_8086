#define _CRT_SECURE_NO_WARNINGS

#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"
#include "../src/simulator.cpp"

namespace test_cpu
{
    using simulator::ExecuteInstructions;

    const uint8_t NASM_CMD_MAX_LEN = 32;
    const uint16_t FILE_PATH_MAX_LEN = 256;
    const uint16_t FILE_DATA_MAX_LEN = 8192;

    size_t ReadFileData(char *data, FILE *file)
    {
        size_t file_size = fread(data, 1, FILE_DATA_MAX_LEN, file);
        data[file_size] = '\0';

        return file_size;
    }

    TEST_CASE("Instructions are decoded correctly")
    {
        const char *file_name = "listing_0042_completionist_decode";

        char input_file_path[FILE_PATH_MAX_LEN];
        snprintf(input_file_path, FILE_PATH_MAX_LEN, "data/%s", file_name);

        char output_file_path[FILE_PATH_MAX_LEN];
        snprintf(output_file_path, FILE_PATH_MAX_LEN, "%s", "test.asm");

        char assembled_file_path[FILE_PATH_MAX_LEN];
        snprintf(assembled_file_path, FILE_PATH_MAX_LEN, "%s", "test.bin");

        FILE *output_file = fopen(output_file_path, "w");
        REQUIRE(output_file != NULL);

        fprintf(output_file, "bits 16\n");

        ExecuteInstructions(output_file, input_file_path, false, true, false, false, false);

        fclose(output_file);

        char nasm_cmd[NASM_CMD_MAX_LEN];
        snprintf(nasm_cmd, NASM_CMD_MAX_LEN, "nasm %s -o %s", output_file_path, assembled_file_path);
        system(nasm_cmd);

        FILE *assembled_file = fopen(assembled_file_path, "rb");
        REQUIRE(assembled_file != NULL);

        FILE *input_file = fopen(input_file_path, "rb");
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

    TEST_CASE("Instructions are executed correctly - no instruction pointer")
    {
        const char *file_name = GENERATE(
            "listing_0044_register_movs",
            "listing_0045_challenge_register_movs",
            "listing_0046_add_sub_cmp");

        char input_file_path[FILE_PATH_MAX_LEN];
        snprintf(input_file_path, FILE_PATH_MAX_LEN, "data/%s", file_name);

        char output_file_path[FILE_PATH_MAX_LEN];
        snprintf(output_file_path, FILE_PATH_MAX_LEN, "%s", "test.txt");

        FILE *output_file = fopen(output_file_path, "wb");
        REQUIRE(output_file != NULL);

        char verification_file_path[FILE_PATH_MAX_LEN];
        snprintf(verification_file_path, FILE_PATH_MAX_LEN, "data/%s.txt", file_name);
        FILE *verification_file = fopen(verification_file_path, "r");
        REQUIRE(verification_file != NULL);

        fprintf(output_file, "--- test\\%s execution ---\n", file_name);

        ExecuteInstructions(output_file, input_file_path, true, false, true, true, false);

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

    TEST_CASE("Instructions are executed correctly - with instruction pointer")
    {
        const char *file_name = GENERATE(
            "listing_0048_ip_register",
            "listing_0049_conditional_jumps",
            "listing_0051_memory_mov",
            "listing_0052_memory_add_loop",
            "listing_0053_add_loop_challenge");

        char input_file_path[FILE_PATH_MAX_LEN];
        snprintf(input_file_path, FILE_PATH_MAX_LEN, "data/%s", file_name);

        char output_file_path[FILE_PATH_MAX_LEN];
        snprintf(output_file_path, FILE_PATH_MAX_LEN, "%s", "test.txt");

        FILE *output_file = fopen(output_file_path, "wb");
        REQUIRE(output_file != NULL);

        char verification_file_path[FILE_PATH_MAX_LEN];
        snprintf(verification_file_path, FILE_PATH_MAX_LEN, "data/%s.txt", file_name);
        FILE *verification_file = fopen(verification_file_path, "r");
        REQUIRE(verification_file != NULL);

        fprintf(output_file, "--- test\\%s execution ---\n", file_name);

        ExecuteInstructions(output_file, input_file_path, true, false, true, true, true);

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
