#include "instruction/instruction_input.h"
#include "instruction/instruction_output.h"
#include "instruction/decoder/instruction_decoder.h"

void DecodeInstructions(FILE *output_stream, InstructionInput *instruction_input)
{
    InstructionDecodingContext decoding_context = {};

    while (ReadNextByte(instruction_input, &decoding_context) != 0)
    {
        DecodeInstruction(instruction_input, &decoding_context);

        if (!decoding_context.mnemonic)
        {
            continue;  // unsupported
        }

        PrintInstructionString(output_stream, &decoding_context);

        decoding_context = {};
    }
}
