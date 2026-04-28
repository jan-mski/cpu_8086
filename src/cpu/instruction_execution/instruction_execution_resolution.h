#ifndef CPU_INSTRUCTION_EXECUTION_COMMON_UTILS_H
#define CPU_INSTRUCTION_EXECUTION_COMMON_UTILS_H

namespace cpu::instruction_execution::resolution
{
    struct ResolvedOperand
    {
        instruction::OperandType type;
        cpu::core::CpuState *cpu_state;
        memory::Memory *memory;
        bool is_instruction_wide;

        union
        {
            core::Register8BitId register_8_bit_id;
            core::Register16BitId register_16_bit_id;
            uint32_t memory_address;
            uint16_t immediate_value;
            int16_t ip_increment;
        };

        int32_t GetValue();

        void SetValue(int32_t value);
    };

    struct ResolvedInstruction
    {
        ResolvedOperand operand_1;
        ResolvedOperand operand_2;
        bool is_instruction_wide;
    };

    uint32_t ResolveEffectiveAddress(cpu::instruction::MemoryAddress *memory_address, cpu::core::CpuState *cpu_state);

    ResolvedOperand ResolveOperand(cpu::instruction::Operand *operand,
                                   cpu::core::CpuState *cpu_state,
                                   memory::Memory *memory,
                                   bool is_instruction_wide);
}

#endif // CPU_INSTRUCTION_EXECUTION_COMMON_UTILS_H
