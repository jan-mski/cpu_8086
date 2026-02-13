#pragma once

#include <cstdio>
#include "../types.h"

const uint8_t OP_MAX_LEN = 6;
const uint8_t ASM_STR_MAX_LEN = 64;

struct OpDecodeData
{
    FILE *input_stream = 0;
    uint8_t bytes[OP_MAX_LEN] = {};
    uint8_t num_bytes_read = 0;
    uint8_t w = 0;                   // 1 bit
    uint8_t d = 0;                   // 1 bit
    uint8_t mod = 0;                 // 2 bits
    uint8_t reg = 0;                 // 3 bits
    uint8_t r_m = 0;                 // 3 bits
    uint16_t data = 0;               // 8/16 bits
    uint16_t addr = 0;               // 8/16 bits
    int32_t displacement = 0;        // 8/16 bits
    char asm_str[ASM_STR_MAX_LEN] = {};
};

void DecodeOps(char **output_buffer, FILE *input_stream);
void DecodeOp(OpDecodeData *decode_data);
size_t ReadNextByte(OpDecodeData *decode_data);
