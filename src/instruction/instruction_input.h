#pragma once

#include <cstdio>
#include "instruction.h"

struct InstructionInput
{
    FILE *stream;
};

size_t ReadNextByte(const InstructionInput *instruction_input, InstructionDecodingContext *decoding_context);
void ReadNextBytesToIndex(const InstructionInput *instruction_input, InstructionDecodingContext *decoding_context, uint8_t byte_index);
