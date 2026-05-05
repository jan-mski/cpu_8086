#ifndef INSTRUCTION_EXECUTION_RESOLUTION_H
#define INSTRUCTION_EXECUTION_RESOLUTION_H

namespace instruction_execution::resolution
{
    struct ResolvedOperand
    {
        instruction::Operand* operand;
        memory::Address resolved_ea;
    };

    struct ResolvedInstruction
    {
        ResolvedOperand operands[instruction::OPERANDS_MAX_LEN];
        bool is_wide;
        memory::Address resolved_ea;
    };

    memory::Address ResolveEffectiveAddress(instruction::MemoryAddress* memory_address,
                                            cpu::CpuState* cpu_state);

    I32 GetResolvedOperandValue(ResolvedOperand* resolved_operand,
                                bool is_instruction_wide,
                                cpu::CpuState* cpu_state,
                                memory::Memory* memory);

    void SetResolvedOperandValue(ResolvedOperand* resolved_operand,
                                 bool is_instruction_wide,
                                 U16 value,
                                 cpu::CpuState* cpu_state,
                                 memory::Memory* memory);

    ResolvedInstruction ResolveInstruction(instruction::Operand* operands,
                                           U8 num_operands,
                                           bool is_wide,
                                           cpu::CpuState* cpu_state);
}

#endif // INSTRUCTION_EXECUTION_RESOLUTION_H
