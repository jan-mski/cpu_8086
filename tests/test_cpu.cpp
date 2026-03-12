#define _CRT_SECURE_NO_WARNINGS

#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"
#include "../src/cpu.cpp"

TEST_CASE("Instructions are decoded correctly")
{
    const char* file_name = "listing_0042_completionist_decode";

    char input_file_path[256];
    snprintf(input_file_path, 256, "data/%s", file_name);

    FILE *input_file = fopen(input_file_path, "rb");
    REQUIRE(input_file != NULL);

    FILE *asm_file = fopen("test.asm", "w");
    REQUIRE(asm_file != NULL);

    fprintf(asm_file, "bits 16\n");

    ExecuteInstructions(asm_file, input_file, true, false);

    fclose(input_file);
    fclose(asm_file);

    char nasm_cmd[32];
    snprintf(nasm_cmd, 32, "nasm test.asm -o test.bin");
    system(nasm_cmd);

    FILE *assembled_file = fopen("test.bin", "rb");
    REQUIRE(assembled_file != NULL);

    input_file = fopen(input_file_path, "rb");
    REQUIRE(input_file != NULL);

    fseek(assembled_file, 0, SEEK_END);
    fseek(input_file, 0, SEEK_END);
    const long assembled_file_size = ftell(assembled_file);
    const long input_file_size = ftell(input_file);
    fseek(assembled_file, 0, SEEK_SET);
    fseek(input_file, 0, SEEK_SET);

    char *assembled_data = (char *) malloc(assembled_file_size);
    char *original_data = (char *) malloc(input_file_size);
    fread(assembled_data, 1, assembled_file_size, assembled_file);
    fread(original_data, 1, input_file_size, input_file);

    bool match = (assembled_file_size == input_file_size) && (memcmp(assembled_data, original_data, assembled_file_size) == 0);

    printf("Output for file (match=%i) '%s':\n", match, file_name);
    asm_file = fopen("test.asm", "r");
    char output_buffer[64];
    while (fgets(output_buffer, 64, asm_file))
    {
        printf("%s", output_buffer);
    }
    fclose(asm_file);

    free(assembled_data);
    free(original_data);
    fclose(assembled_file);
    fclose(input_file);

    REQUIRE(match);
}

TEST_CASE("Register MOVs are executed correctly")
{
    const char* file_name = GENERATE("listing_0044_register_movs",
                                     "listing_0045_challenge_register_movs");

    char input_file_path[256];
    snprintf(input_file_path, 256, "data/%s", file_name);

    FILE *input_file = fopen(input_file_path, "rb");
    REQUIRE(input_file != NULL);

    FILE *output_file = fopen("test.txt", "wb");
    REQUIRE(output_file != NULL);

    ExecuteInstructions(output_file, input_file, false, true);

    fclose(input_file);
    fclose(output_file);

    output_file = fopen("test.txt", "rb");
    REQUIRE(output_file != NULL);

    char verification_file_path[256];
    snprintf(verification_file_path, 256, "data/%s.txt", file_name);
    FILE *verification_file = fopen(verification_file_path, "r");
    REQUIRE(verification_file != NULL);

    fseek(output_file, 0, SEEK_END);
    const long output_file_size = ftell(output_file);
    fseek(verification_file, 0, SEEK_END);
    const long verification_file_size = ftell(verification_file);
    fseek(output_file, 0, SEEK_SET);
    fseek(verification_file, 0, SEEK_SET);

    char *output_data = (char *) malloc(output_file_size);
    char *verification_data = (char *) malloc(verification_file_size);
    fread(output_data, 1, output_file_size, output_file);

    char line[256];
    bool reg_values_header_found = false;
    int verification_data_size = 0;
    while (fgets(line, 256, verification_file))
    {
        if (!reg_values_header_found)
        {
            if (strcmp(line, "--- final register values ---\n") == 0)
            {
                reg_values_header_found = true;
            }
        }
        else if (strcmp(line, "\n") != 0)
        {
            verification_data_size += sprintf(verification_data + verification_data_size, "%s", line);
        }
    }
    sprintf(verification_data + verification_data_size, "%s", "\0");

    bool match = (output_file_size == verification_data_size) && (memcmp(output_data, verification_data, verification_data_size) == 0);

    printf("Output for file (match=%i) '%s':\n", match, file_name);
    output_file = fopen("test.txt", "rb");
    char output_buffer[64];
    while (fgets(output_buffer, 64, output_file) != 0)
    {
        printf("%s", output_buffer);
    }
    fclose(output_file);

    free(output_data);
    free(verification_data);
    fclose(verification_file);
    fclose(input_file);

    REQUIRE(match);
}