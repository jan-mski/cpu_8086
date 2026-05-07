#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstdarg>

#include <utility>
#include <type_traits>

#include "base.h"
#include "simulator.h"
#include "memory.h"
#include "cpu.h"
#include "instruction.h"
#include "instruction_decoding/instruction_decoding_inc.h"
#include "instruction_execution/instruction_execution_inc.h"
#include "cycle_estimation.h"
#include "text_output.h"

// NOTE: Single translation unit let's go - the unorthodox but efficient ways of Casey Muratori
#include "memory.cpp"
#include "cpu.cpp"
#include "instruction_decoding/instruction_decoding_inc.cpp"
#include "instruction_execution/instruction_execution_inc.cpp"
#include "cycle_estimation.cpp"
#include "text_output.cpp"

namespace simulator
{
    namespace mem = ::memory;
    namespace cpu = ::cpu;
    namespace ins = ::instruction;
    namespace exe = ::instruction_execution::core;
    namespace dec = ::instruction_decoding::core;
    namespace dec_ctx = ::instruction_decoding::context;
    namespace txt = ::text_output;
    namespace cyc = ::cycle_estimation;

    void ExecuteInstructions(cpu::CpuState* cpu_state,
                             mem::Memory* memory,
                             FILE* output_stream,
                             U16 num_instruction_bytes,
                             ProgramFlags program_flags)
    {
        ProgramFlags print_execution_trace = program_flags & ProgramFlag_PrintExecutionTrace;

        dec_ctx::DecodingContext decoding_context = {};
        cyc::CycleCountEstimate cycle_count_estimate = {};

        U16 ip_value;
        while ((ip_value = cpu::GetRegisterValue(cpu_state, cpu::Register16BitId_IP)) < num_instruction_bytes)
        {
            dec_ctx::ReadNextInstructionByte(&decoding_context, ip_value, memory);
            ins::Instruction instruction = dec::DecodeInstruction(&decoding_context, cpu_state, memory);

            cpu::CpuState pre_execution_state = {};
            if (print_execution_trace)
            {
                pre_execution_state = *cpu_state;
            }

            if (instruction.mnemonic == ins::Mnemonic_None)
            {
                fprintf(stderr, "Unsupported instruction. Terminating.");
                break;
            }

            if (program_flags & ProgramFlag_PrintAsmString)
            {
                txt::PrintAsmString(output_stream, &instruction);
            }

            cpu::IncrementIP(cpu_state, decoding_context.num_bytes_read);

            if (program_flags & ProgramFlag_Execute)
            {
                exe::ExecutionResult execution_result = exe::ExecuteInstruction(&instruction, cpu_state, memory);

                if (print_execution_trace)
                {
                    cyc::UpdateCycleEstimate(&cycle_count_estimate, &instruction, execution_result);
                }
            }

            if (print_execution_trace)
            {
                txt::PrintExecutionTrace(
                    output_stream,
                    &instruction,
                    &pre_execution_state,
                    cpu_state,
                    cycle_count_estimate);
            }

            decoding_context = {};
        }

        if (program_flags & ProgramFlag_PrintFinalState)
        {
            txt::PrintFinalCpuState(output_stream, cpu_state);
        }
    }

    void ExecuteInstructions(FILE* output_stream,
                             const char* input_file_path,
                             ProgramFlags program_flags)
    {
        cpu::CpuState cpu_state = {};
        mem::Memory* memory = new mem::Memory();
        U16 num_bytes_loaded = mem::LoadFileToMemory(memory, input_file_path);

        ExecuteInstructions(
            &cpu_state,
            memory,
            output_stream,
            num_bytes_loaded,
            program_flags);

        if (program_flags & ProgramFlag_DumpMemory)
        {
            mem::SaveMemoryToFile("memory_dump.data", memory);
        }

        delete memory;
    }
}
