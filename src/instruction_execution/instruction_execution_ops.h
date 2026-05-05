#ifndef INSTRUCTION_EXECUTION_OPS_H
#define INSTRUCTION_EXECUTION_OPS_H

namespace instruction_execution::ops
{
    typedef U16 OpResult;

    typedef OpResult (* Op)(resolution::ResolvedInstruction* resolved_instruction,
                            cpu::CpuState* cpu_state,
                            memory::Memory* memory);

    OpResult noop(resolution::ResolvedInstruction* resolved_instruction,
                  cpu::CpuState* cpu_state,
                  memory::Memory* memory);

    OpResult add(resolution::ResolvedInstruction* resolved_instruction,
                 cpu::CpuState* cpu_state,
                 memory::Memory* memory);

    OpResult subtract(resolution::ResolvedInstruction* resolved_instruction,
                      cpu::CpuState* cpu_state,
                      memory::Memory* memory);

    OpResult bitwise_not(resolution::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         memory::Memory* memory);

    OpResult bitwise_and(resolution::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         memory::Memory* memory);

    OpResult bitwise_or(resolution::ResolvedInstruction* resolved_instruction,
                        cpu::CpuState* cpu_state,
                        memory::Memory* memory);

    OpResult bitwise_xor(resolution::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         memory::Memory* memory);

    OpResult bitwise_shl(resolution::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         memory::Memory* memory);

    OpResult bitwise_shr(resolution::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         memory::Memory* memory);

    OpResult bitwise_sar(resolution::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         memory::Memory* memory);
}

#endif // INSTRUCTION_EXECUTION_OPS_H
