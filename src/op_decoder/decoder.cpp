#define _CRT_SECURE_NO_WARNINGS

#include "decoder.h"

void GetAsmString(char *dest, const OpDecodeData *decode_data)
{
    snprintf(dest, ASM_STR_MAX_LEN, "%s %s, %s", decode_data->mnemonic, decode_data->left_operand,
        decode_data->right_operand);
}

void DecodeOps(char **output_buffer, FILE *input_stream)
{
    OpDecodeData decode_data = {input_stream};

    uint8_t op_index = 0;
    while (ReadNextByte(&decode_data) != 0)
    {
        DecodeOp(&decode_data);

        if (decode_data.mnemonic == 0)
        {
            continue;  // unsupported
        }

        GetAsmString(output_buffer[op_index++], &decode_data);

        decode_data = {input_stream};
    }
    output_buffer[op_index] = 0;
}

size_t ReadNextByte(OpDecodeData *decode_data)
{
    const size_t num_bytes_read = fread(decode_data->bytes + decode_data->num_bytes_read, sizeof(uint8_t), 1,
        decode_data->input_stream);
    decode_data->num_bytes_read += num_bytes_read;

    return num_bytes_read;
}
