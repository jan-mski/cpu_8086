#define _CRT_SECURE_NO_WARNINGS

#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void DecodeOps(char **output_buffer, FILE *input_stream);

TEST_CASE("Instructions are decoded correctly")
{
    const char* file_name = GENERATE("listing_0037_single_register_mov",
                                     "listing_0038_many_register_mov",
                                     "listing_0039_more_movs",
                                     "listing_0040_challenge_movs",
                                     "listing_0041_add_sub_cmp_jnz");

    char input_path[256], nasm_cmd[512];
    sprintf(input_path, "data/%s", file_name);

    FILE *input = fopen(input_path, "rb");
    FILE *asm_file = fopen("test.asm", "w");
    fprintf(asm_file, "bits 16\n");

    char *output_buffer[128] = {};
    for (uint8_t i = 0; i < 128; ++i)
    {
        output_buffer[i] = new char[64];
    }
    DecodeOps(output_buffer, input);

    for (int i = 0; i < 128; ++i)
    {
        const char *asm_str = output_buffer[i];
        if (asm_str == 0)
        {
            break;
        }
        fprintf(asm_file, "%s\n", asm_str);
    }
    fclose(input);
    fclose(asm_file);

    sprintf(nasm_cmd, "nasm test.asm -o test.bin");
    system(nasm_cmd);

    FILE *assembled = fopen("test.bin", "rb");
    input = fopen(input_path, "rb");

    fseek(assembled, 0, SEEK_END);
    fseek(input, 0, SEEK_END);
    long assembled_size = ftell(assembled);
    long input_size = ftell(input);
    fseek(assembled, 0, SEEK_SET);
    fseek(input, 0, SEEK_SET);

    char *assembled_data = (char *) malloc(assembled_size);
    char *original_data = (char *) malloc(input_size);
    fread(assembled_data, 1, assembled_size, assembled);
    fread(original_data, 1, input_size, input);

    int match = (assembled_size == input_size) && (memcmp(assembled_data, original_data, assembled_size) == 0);

    if (!match) {
        printf("Invalid output for file '%s':\n", file_name);
        for (int i = 0; i < 128; ++i) {
            const char *asm_str = output_buffer[i];
            if (asm_str == 0)
            {
                break;
            }
            printf("%s\n", output_buffer[i]);
        }
    }

    for (int i = 0; i < 128; ++i)
    {
        delete[] output_buffer[i];
    }
    free(assembled_data);
    free(original_data);
    fclose(assembled);
    fclose(input);

    REQUIRE(match);
}