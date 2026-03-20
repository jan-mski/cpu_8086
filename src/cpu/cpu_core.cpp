#include <cstdio>
#include <cstdint>
#include <cstring>

// NOTE: Single translation unit let's go - learning from Casey Muratori
#include "cpu_core.h"
#include "cpu_state.h"
#include "cpu_instruction.h"
#include "cpu_instruction_input.h"
#include "cpu_instruction_decoding.h"
#include "cpu_instruction_decoding_specs.inl"
#include "cpu_instruction_execution.h"
#include "cpu_text_output.h"

#include "cpu_state.cpp"
#include "cpu_instruction_input.cpp"
#include "cpu_instruction_decoding.cpp"
#include "cpu_instruction_execution.cpp"
#include "cpu_text_output.cpp"

namespace cpu::core
{
    using cpu::state::CpuState;
    using cpu::instruction::Instruction;
    using cpu::instruction::Mnemonic;
    using cpu::instruction_input::InstructionInput;
    using cpu::instruction_decoding::core::DecodeInstruction;
    using cpu::instruction_decoding::context::InstructionDecodeContext;
    using cpu::instruction_decoding::context::ReadNextByte;
    using cpu::instruction_execution::ExecuteInstruction;
    using cpu::text_output::PrintAsmString;
    using cpu::text_output::PrintExecutionTrace;
    using cpu::text_output::PrintFinalCpuState;

    void ExecuteInstructions(FILE *output_stream,
                             FILE *input_stream,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace)
    {
        CpuState cpu_state = CpuState();
        InstructionInput instruction_input = {input_stream};
        InstructionDecodeContext decoding_context = {};

        while (ReadNextByte(&decoding_context, &instruction_input) != 0)
        {
            Instruction instruction = DecodeInstruction(&decoding_context, &instruction_input);

            if (instruction.mnemonic == Mnemonic::None)
            {
                fprintf(stderr, "Unsupported instruction. Terminating.");
                break;
            }

            if (print_asm_strings)
            {
                PrintAsmString(output_stream, &instruction);
            }

            CpuState pre_execution_state;
            if (print_execution_trace)
            {
                pre_execution_state = cpu_state;
            }

            ExecuteInstruction(&instruction, &cpu_state);

            if (print_execution_trace)
            {
                PrintExecutionTrace(output_stream, &instruction, &pre_execution_state, &cpu_state);
            }

            decoding_context = {};
        }

        if (print_final_state)
        {
            PrintFinalCpuState(output_stream, &cpu_state);
        }
    }
}
