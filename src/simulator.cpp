#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <utility>

// NOTE: Single translation unit let's go - learning from Casey Muratori
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
    using cpu::core::Cpu;
    using cpu::core::RegisterId;
    using cpu::core::GetRegisterValue;
    using cpu::core::SetRegisterValue;
    using cpu::instruction::Instruction;
    using cpu::instruction::Mnemonic;
    using cpu::instruction_decoding::core::DecodeInstruction;
    using cpu::instruction_decoding::context::DecodingContext;
    using cpu::instruction_decoding::context::ReadNextInstructionByte;
    using cpu::instruction_execution::ExecuteInstruction;
    using text_output::PrintAsmString;
    using text_output::PrintExecutionTrace;
    using text_output::PrintFinalCpuState;

    void IncrementInstructionPointer(Cpu *cpu, uint8_t increment)
    {
        SetRegisterValue(
            cpu->registers,
            RegisterId::IP,
            GetRegisterValue(cpu->registers, RegisterId::IP) + increment);
    }

    void ExecuteInstructions(Cpu *cpu,
                             Memory *memory,
                             FILE *output_stream,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace,
                             bool print_instruction_pointer)
    {
        DecodingContext decoding_context = {};

        while (ReadNextInstructionByte(&decoding_context, cpu, memory) != 0)
        {
            Instruction instruction = DecodeInstruction(&decoding_context, cpu, memory);

            Cpu pre_execution_state;
            if (print_execution_trace)
            {
                pre_execution_state = *cpu;
            }

            IncrementInstructionPointer(cpu, decoding_context.num_bytes_read);

            if (instruction.mnemonic == Mnemonic::None)
            {
                fprintf(stderr, "Unsupported instruction. Terminating.");
                break;
            }

            if (print_asm_strings)
            {
                PrintAsmString(output_stream, &instruction);
            }

            ExecuteInstruction(&instruction, cpu);

            if (print_execution_trace)
            {
                PrintExecutionTrace(output_stream, &instruction, &pre_execution_state, cpu, print_instruction_pointer);
            }

            decoding_context = {};
        }

        if (print_final_state)
        {
            PrintFinalCpuState(output_stream, cpu, print_instruction_pointer);
        }
    }

    void ExecuteInstructions(FILE *output_stream,
                             const char *input_file_path,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace,
                             bool print_instruction_pointer)
    {
        Cpu cpu = Cpu();
        Memory *memory = new Memory();
        LoadFileToMemory(memory, input_file_path);

        ExecuteInstructions(
            &cpu,
            memory,
            output_stream,
            print_asm_strings,
            print_final_state,
            print_execution_trace,
            print_instruction_pointer);

        delete memory;
    }
}
