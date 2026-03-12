#include <cstdio>
#include <cstdint>

#include "cpu.h"
#include "cpu_registers.h"
#include "instruction/instruction.h"
#include "instruction/instruction_input.h"
#include "instruction/decoder/instruction_decoder.h"
#include "instruction/decoder/instruction_specs.inl"
#include "instruction/decoder/instruction_field_decoder.h"
#include "instruction/decoder/instruction_operand_decoder.h"
#include "instruction/instruction_executor.h"
#include "text_output.h"

#include "cpu_registers.cpp"
#include "instruction/instruction_input.cpp"
#include "instruction/decoder/instruction_field_decoder.cpp"
#include "instruction/decoder/instruction_operand_decoder.cpp"
#include "instruction/decoder/instruction_decoder.cpp"
#include "instruction/instruction_executor.cpp"
#include "text_output.cpp"

void ExecuteInstructions(FILE *output_stream,
                         FILE *input_stream,
                         bool print_instruction_strings,
                         bool print_register_values)
{
    InstructionInput instruction_input = {input_stream};
    DecodingContext decoding_context = {};

    while (ReadNextByte(&instruction_input, &decoding_context) != 0)
    {
        Instruction instruction = DecodeInstruction(&instruction_input, &decoding_context);

        if (instruction.mnemonic == Mnemonic_None)
        {
            fprintf(stderr, "Unsupported instruction. Terminating.");
            break;
        }

        if (print_instruction_strings)
        {
            PrintInstructionString(output_stream, &instruction);
        }

        ExecuteInstruction(&instruction);

        decoding_context = {};
    }

    if (print_register_values)
    {
        PrintRegisterValues(output_stream);
    }
}
