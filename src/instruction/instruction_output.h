#pragma once

#include "../instruction/instruction.h"

const uint8_t INSTRUCTION_STR_MAX_LEN = 64;

void PrintInstructionString(FILE *output_stream, const InstructionDecodingContext *decoding_context);
