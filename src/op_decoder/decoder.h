#pragma once

#include <cstdio>
#include "../types.h"

const uint8_t OP_MAX_LEN = 6;
const uint8_t ASM_STR_MAX_LEN = 64;
const uint8_t OPERAND_MAX_LEN = 24;

struct OpDecodeData
{
    FILE *input_stream;
    uint8_t bytes[OP_MAX_LEN];
    uint8_t num_bytes_read;
    bool w;                          // 1 bit
    bool d;                          // 1 bit
    bool s;                          // 1 bit
    uint8_t mod;                     // 2 bits
    uint8_t reg;                     // 3 bits
    uint8_t r_m;                     // 3 bits
    uint16_t data;                   // 8/16 bits
    uint16_t addr;                   // 8/16 bits
    int32_t displacement;            // 8/16 bits

    const char *mnemonic;
    char left_operand[OPERAND_MAX_LEN];
    char right_operand[OPERAND_MAX_LEN];
};

void DecodeOps(char **output_buffer, FILE *input_stream);
void DecodeOp(OpDecodeData *decode_data);
size_t ReadNextByte(OpDecodeData *decode_data);
