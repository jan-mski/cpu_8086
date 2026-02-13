#define _CRT_SECURE_NO_WARNINGS

#include "decoder.h"

uint8_t GetAsmStrLen(const OpDecodeData *decode_data)
{
    uint8_t len = 0;
    for (len = 0; len < ASM_STR_MAX_LEN; ++len)
    {
        if (decode_data->asm_str[len] == '\0')
        {
            break;
        }
    }

    return len;
}

void CopyAsmStr(char *dest, const OpDecodeData *decode_data)
{
    for (uint8_t i = 0; i < ASM_STR_MAX_LEN; ++i)
    {
        const char current_char = decode_data->asm_str[i];
        dest[i] = current_char;
        if (current_char == '\0')
        {
            break;
        }
    }
}

void DecodeOps(char **output_buffer, FILE *input_stream)
{
    OpDecodeData decode_data = {input_stream};

    uint8_t op_index = 0;
    while (ReadNextByte(&decode_data) != 0)
    {
        DecodeOp(&decode_data);

        const uint8_t asm_str_len = GetAsmStrLen(&decode_data);
        if (asm_str_len == 0)
        {
            continue;  // unsupported
        }

        char *output_buffer_slot = new char[ASM_STR_MAX_LEN];
        CopyAsmStr(output_buffer_slot, &decode_data);
        output_buffer[op_index++] = output_buffer_slot;

        decode_data = {input_stream};
    }
}

size_t ReadNextByte(OpDecodeData *decode_data)
{
    const size_t num_bytes_read = fread(decode_data->bytes + decode_data->num_bytes_read, sizeof(uint8_t), 1,
        decode_data->input_stream);
    decode_data->num_bytes_read += num_bytes_read;

    return num_bytes_read;
}
