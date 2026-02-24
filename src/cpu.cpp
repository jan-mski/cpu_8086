// NOTE: Learning from the best here (Casey Muratori:)
#include <cstdio>
#include <cstdint>

#include "cpu.h"
#include "instruction/instruction.h"

#include "instruction/instruction_input.h"
#include "instruction/instruction_input.cpp"

#include "instruction/instruction_output.h"
#include "instruction/instruction_output.cpp"

#include "instruction/decoder/instruction_field_decoder.h"
#include "instruction/decoder/instruction_field_decoder.cpp"

#include "instruction/decoder/instruction_operand_decoder.h"
#include "instruction/decoder/instruction_operand_decoder.cpp"

#include "instruction/decoder/instruction_decoder.h"
#include "instruction/decoder/instruction_decoder.cpp"

void DecodeInstructions(FILE *output_stream, FILE *input_stream)
{
    InstructionInput instruction_input = {input_stream};
    DecodingContext decoding_context = {};

    while (ReadNextByte(&instruction_input, &decoding_context) != 0)
    {
        DecodeInstruction(&instruction_input, &decoding_context);

        if (decoding_context.mnemonic == MNEMONIC_NONE)
        {
            fprintf(stderr, "Unsupported instruction. Terminating.");
            break;
        }

        PrintInstructionString(output_stream, &decoding_context);

        decoding_context = {};
    }
}
