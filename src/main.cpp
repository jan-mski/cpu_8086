#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include "op_decoder/decoder.h"

const uint8_t OUTPUT_BUFFER_SIZE = 128;

void AllocateOutputBuffer(char *output_buffer[128])
{
    for (uint8_t i = 0; i < OUTPUT_BUFFER_SIZE; ++i)
    {
        output_buffer[i] = new char[ASM_STR_MAX_LEN];
    }
}

void ReleaseOutputBuffer(char *output_buffer[128])
{
    for (uint8_t i = 0; i < OUTPUT_BUFFER_SIZE; ++i)
    {
        delete[] output_buffer[i];
    }
}

void PrintAssemblyStrings(char *output_buffer[128])
{
    for (uint8_t i = 0; i < OUTPUT_BUFFER_SIZE; ++i)
    {
        const char *asm_str = output_buffer[i];
        if (asm_str == 0)
        {
            break;
        }
        printf("%s\n", asm_str);
    }
}

int main(int argc, char *argv[])
{
    const char *filepath = argv[1];

    FILE *file = fopen(filepath, "rb");
    if (file == 0)
    {
        printf("File read error\n");
        return 1;
    }

    char *output_buffer[OUTPUT_BUFFER_SIZE] = {};
    AllocateOutputBuffer(output_buffer);
    DecodeOps(output_buffer, file);
    PrintAssemblyStrings(output_buffer);
    ReleaseOutputBuffer(output_buffer);

    fclose(file);

    return 0;
}
