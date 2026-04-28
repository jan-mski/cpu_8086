#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstdarg>

#include <utility>

#include "simulator.h"
#include "memory.h"
#include "cpu/cpu_inc.h"
#include "text_output.h"

// NOTE: Single translation unit let's go - the unorthodox but efficient ways of Casey Muratori
#include "memory.cpp"
#include "cpu/cpu_inc.cpp"
#include "text_output.cpp"

namespace simulator
{
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::core::Register16BitId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Mnemonic;
    using cpu::instruction_decoding::core::DecodeInstruction;
    using cpu::instruction_decoding::context::DecodingContext;
    using cpu::instruction_decoding::context::ReadNextInstructionByte;
    using cpu::instruction_execution::core::ExecuteInstruction;
    using text_output::PrintAsmString;
    using text_output::PrintExecutionTrace;
    using text_output::PrintFinalCpuState;

    void ExecuteInstructions(CpuState *cpu_state,
                             Memory *memory,
                             FILE *output_stream,
                             uint16_t num_instruction_bytes,
                             bool execute_instructions,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace)
    {
        DecodingContext decoding_context = {};

        uint32_t ip_value;
        while ((ip_value = cpu_state->GetRegisterValue(Register16BitId::IP)) < num_instruction_bytes)
        {
            ReadNextInstructionByte(&decoding_context, ip_value, memory);
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

            cpu_state->IncrementIP(decoding_context.num_bytes_read);

            if (execute_instructions)
            {
                ExecuteInstruction(&instruction, cpu_state, memory);
            }

            if (print_execution_trace)
            {
                PrintExecutionTrace(
                    output_stream,
                    &instruction,
                    &pre_execution_state,
                    cpu_state);
            }

            decoding_context = {};
        }

        if (print_final_state)
        {
            PrintFinalCpuState(output_stream, cpu_state);
        }
    }

    void ExecuteInstructions(FILE *output_stream,
                             const char *input_file_path,
                             bool execute_instructions,
                             bool dump_memory,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace)
    {
        CpuState cpu_state = {};
        Memory *memory = new Memory();
        uint16_t num_bytes_loaded = Memory::LoadFileToMemory(memory, input_file_path);

        ExecuteInstructions(
            &cpu_state,
            memory,
            output_stream,
            num_bytes_loaded,
            execute_instructions,
            print_asm_strings,
            print_final_state,
            print_execution_trace);

        if (dump_memory)
        {
            Memory::SaveMemoryToFile("memory_dump.data", memory);
        }

        delete memory;
    }
}
