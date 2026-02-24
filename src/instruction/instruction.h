#pragma once

#include "../types.h"

const uint8_t INSTRUCTION_MAX_LEN = 6;
const uint8_t REGISTER_NAMES_MAX_LEN = 2;

enum OperandType
{
    OPERAND_NONE,
    OPERAND_REGISTER,
    OPERAND_MEMORY_ADDRESS,
    OPERAND_IMMEDIATE,
    OPERAND_LABEL_LIKE_DISPLACEMENT
};

struct MemoryAddress
{
    bool direct;
    const char *qualifier;
    const char **register_names;
    int32_t displacement;
};

struct Operand
{
    OperandType type;
    const char *register_name;
    MemoryAddress memory_address;
    uint16_t immediate_value;
    int32_t label_like_displacement;
};

struct InstructionDecodingContext
{
    uint8_t bytes[INSTRUCTION_MAX_LEN];
    uint8_t num_bytes_read;
    bool w;                          // 1 bit
    bool d;                          // 1 bit
    bool s;                          // 1 bit
    uint8_t mod;                     // 2 bits
    uint8_t reg;                     // 3 bits
    uint8_t r_m;                     // 3 bits
    uint8_t common_mnemonic;         // 3 bits
    uint16_t data;                   // 8/16 bits
    uint16_t addr;                   // 8/16 bits
    int32_t displacement;            // 8/16 bits

    const char *mnemonic;
    Operand operands[2];
};
