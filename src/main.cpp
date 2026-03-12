#define _CRT_SECURE_NO_WARNINGS

#include <cstring>

// NOTE: Single translation unit let's go - learning from Casey Muratori here
#include "cpu.cpp"

int main(int argc, char *argv[])
{
    if (argc == 0)
    {
        fprintf(stderr, "No file specified\n");
    }
    const char *filepath = argv[1];
    bool print_instructions = false;
    bool print_registers = false;
    for (uint8_t i = 2; i < argc; ++i)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            print_instructions = true;
        }
        if (strcmp(argv[i], "-r") == 0)
        {
            print_registers = true;
        }
    }

    FILE *file = fopen(filepath, "rb");
    if (file == 0)
    {
        printf("Error reading file: %s\n", filepath);
        return 1;
    }

    ExecuteInstructions(stdout, file, print_instructions, print_registers);

    fclose(file);

    return 0;
}
