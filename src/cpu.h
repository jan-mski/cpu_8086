#pragma once

#include <cstdio>
#include "instruction/instruction_input.h"

void DecodeInstructions(FILE *output_stream, InstructionInput *instruction_input);
