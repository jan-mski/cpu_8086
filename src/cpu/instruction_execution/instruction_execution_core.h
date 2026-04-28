#ifndef CPU_INSTRUCTION_EXECUTION_CORE_H
#define CPU_INSTRUCTION_EXECUTION_CORE_H

namespace cpu::instruction_execution::core
{
    void ExecuteInstruction(
        cpu::instruction::Instruction *instruction,
        cpu::core::CpuState *cpu_state,
        memory::Memory *memory);
}

#endif // CPU_INSTRUCTION_EXECUTION_CORE_H
