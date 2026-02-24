#define _CRT_SECURE_NO_WARNINGS

#include "cpu.h"
#include "instruction/instruction_input.h"

int main(int argc, char *argv[])
{
    const char *filepath = argv[1];

    FILE *file = fopen(filepath, "rb");
    if (file == 0)
    {
        printf("Error reading file: %s\n", filepath);
        return 1;
    }

    DecodeInstructions(stdout, file);

    fclose(file);

    return 0;
}
