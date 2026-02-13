#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include "op_decoder/decoder.h"

const uint8_t OUTPUT_BUFFER_SIZE = 128;

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

    DecodeOps(output_buffer, file);

    for (uint8_t i = 0; i < OUTPUT_BUFFER_SIZE; ++i)
    {
        const char *asm_str = output_buffer[i];
        if (asm_str == 0)
        {
            break;
        }
        printf("%s\n", asm_str);
        delete[] asm_str;
    }

    fclose(file);

    return 0;
}
