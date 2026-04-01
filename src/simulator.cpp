#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <utility>

// NOTE: Single translation unit let's go - the unorthodox but efficient ways of Casey Muratori
#include "simulator.h"
#include "memory.h"
#include "cpu/cpu_core.h"
#include "cpu/cpu_instruction.h"
#include "cpu/cpu_instruction_decoding.h"
#include "cpu/cpu_instruction_decoding_specs.inl"
#include "cpu/cpu_instruction_execution.h"
#include "text_output.h"

#include "memory.cpp"
#include "cpu/cpu_core.cpp"
#include "cpu/cpu_instruction_decoding.cpp"
#include "cpu/cpu_instruction_execution.cpp"
#include "text_output.cpp"

namespace simulator
{
    using memory::Memory;
    using memory::LoadFileToMemory;
    using cpu::core::CpuState;
    using cpu::core::RegisterId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Mnemonic;
    using cpu::instruction_decoding::core::DecodeInstruction;
    using cpu::instruction_decoding::context::DecodingContext;
    using cpu::instruction_decoding::context::ReadNextInstructionByte;
    using cpu::instruction_execution::ExecuteInstruction;
    using text_output::PrintAsmString;
    using text_output::PrintExecutionTrace;
    using text_output::PrintFinalCpuState;

    void ExecuteInstructions(CpuState *cpu_state,
                             Memory *memory,
                             FILE *output_stream,
                             bool execute_instructions,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace,
                             bool print_instruction_pointer)
    {
        DecodingContext decoding_context = {};

        while (ReadNextInstructionByte(&decoding_context, cpu_state, memory) != 0)
        {
            Instruction instruction = DecodeInstruction(&decoding_context, cpu_state, memory);

            CpuState pre_execution_state;
            if (print_execution_trace)
            {
                pre_execution_state = *cpu_state;
            }

            if (instruction.mnemonic == Mnemonic::None)
            {
                fprintf(stderr, "Unsupported instruction. Terminating.");
                break;
            }

            if (print_asm_strings)
            {
                PrintAsmString(output_stream, &instruction);
            }

            cpu_state->IncrementInstructionPointer(decoding_context.num_bytes_read);

            if (execute_instructions)
            {
                ExecuteInstruction(&instruction, cpu_state);
            }

            if (print_execution_trace)
            {
                PrintExecutionTrace(
                    output_stream,
                    &instruction,
                    &pre_execution_state,
                    cpu_state,
                    print_instruction_pointer);
            }

            decoding_context = {};
        }

        if (print_final_state)
        {
            PrintFinalCpuState(output_stream, cpu_state, print_instruction_pointer);
        }
    }

    void ExecuteInstructions(FILE *output_stream,
                             const char *input_file_path,
                             bool execute_instructions,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace,
                             bool print_instruction_pointer)
    {
        CpuState cpu_state = CpuState();
        Memory *memory = new Memory();
        LoadFileToMemory(memory, input_file_path);

        ExecuteInstructions(
            &cpu_state,
            memory,
            output_stream,
            execute_instructions,
            print_asm_strings,
            print_final_state,
            print_execution_trace,
            print_instruction_pointer);

        delete memory;
    }
}
