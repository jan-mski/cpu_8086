#define _CRT_SECURE_NO_WARNINGS

#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/cpu.h"

TEST_CASE("Instructions are decoded correctly")
{
    const char* file_name = GENERATE("listing_0037_single_register_mov",
                                     "listing_0038_many_register_mov",
                                     "listing_0039_more_movs",
                                     "listing_0040_challenge_movs",
                                     "listing_0041_add_sub_cmp_jnz");

    char input_path[256], nasm_cmd[512];
    sprintf(input_path, "data/%s", file_name);

    FILE *input_file = fopen(input_path, "rb");
    REQUIRE(input_file != NULL);

    FILE *asm_file = fopen("test.asm", "w");
    REQUIRE(asm_file != NULL);

    fprintf(asm_file, "bits 16\n");

    DecodeInstructions(asm_file, input_file);

    fclose(input_file);
    fclose(asm_file);

    sprintf(nasm_cmd, "nasm test.asm -o test.bin");
    system(nasm_cmd);

    FILE *assembled = fopen("test.bin", "rb");
    REQUIRE(assembled != NULL);

    input_file = fopen(input_path, "rb");
    REQUIRE(input_file != NULL);

    fseek(assembled, 0, SEEK_END);
    fseek(input_file, 0, SEEK_END);
    const long assembled_size = ftell(assembled);
    const long input_size = ftell(input_file);
    fseek(assembled, 0, SEEK_SET);
    fseek(input_file, 0, SEEK_SET);

    char *assembled_data = (char *) malloc(assembled_size);
    char *original_data = (char *) malloc(input_size);
    fread(assembled_data, 1, assembled_size, assembled);
    fread(original_data, 1, input_size, input_file);

    const int match = (assembled_size == input_size) && (memcmp(assembled_data, original_data, assembled_size) == 0);

    if (!match) {
        printf("Invalid output for file '%s':\n", file_name);

        asm_file = fopen("test.asm", "r");

        char output_buffer[64];
        while (fgets(output_buffer, 64, asm_file) != 0)
        {
            printf("%s\n", output_buffer);
        }

        fclose(asm_file);
    }

    free(assembled_data);
    free(original_data);
    fclose(assembled);
    fclose(input_file);

    REQUIRE(match);
}