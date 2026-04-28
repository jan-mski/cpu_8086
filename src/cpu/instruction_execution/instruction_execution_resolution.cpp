namespace cpu::instruction_execution::resolution
{
    using std::to_underlying;
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::core::FlagId;
    using cpu::core::Register8BitId;
    using cpu::core::Register16BitId;
    using cpu::instruction::Operand;
    using cpu::instruction::OperandType;
    using cpu::instruction::MemoryAddress;

    uint32_t ResolveEffectiveAddress(MemoryAddress *memory_address, CpuState *cpu_state)
    {
        int32_t effective_address = memory_address->displacement;
        for (uint8_t i = 0; memory_address->register_ids[i] != Register16BitId::None; ++i)
        {
            effective_address += cpu_state->GetRegisterValue(memory_address->register_ids[i]);
        }

        return (uint32_t) effective_address;
    }

    int32_t ResolvedOperand::GetValue()
    {
        int32_t value = 0;

        switch (type)
        {
            case instruction::OperandType::None:
            {
            } break;
            case instruction::OperandType::Register8Bit:
            {
                value = cpu_state->GetRegisterValue(register_8_bit_id);
            } break;
            case instruction::OperandType::Register16Bit:
            {
                value = cpu_state->GetRegisterValue(register_16_bit_id);
            } break;
            case instruction::OperandType::Immediate:
            {
                value = immediate_value;
            } break;
            case instruction::OperandType::MemoryAddress:
            {
                value = memory->ReadMemory(memory_address, is_instruction_wide);
            } break;
            case instruction::OperandType::IPIncrement:
            {
                value = ip_increment;
            } break;
        }

        return value;
    }

    void ResolvedOperand::SetValue(int32_t value)
    {
        switch (type)
        {
            case instruction::OperandType::None:
            case instruction::OperandType::Immediate:
            case instruction::OperandType::IPIncrement:
            {
            } break;
            case instruction::OperandType::Register8Bit:
            {
                cpu_state->SetRegisterValue(register_8_bit_id, (uint8_t) value);
            } break;
            case instruction::OperandType::Register16Bit:
            {
                cpu_state->SetRegisterValue(register_16_bit_id, (uint16_t) value);
            } break;
            case instruction::OperandType::MemoryAddress:
            {
                memory->WriteMemory(memory_address, is_instruction_wide, (uint16_t) value);
            } break;
        }
    }

    ResolvedOperand ResolveOperand(Operand *operand, CpuState *cpu_state, Memory *memory, bool is_instruction_wide)
    {
        ResolvedOperand resolved_operand = {
            .type = operand->type,
            .cpu_state = cpu_state,
            .memory = memory,
            .is_instruction_wide = is_instruction_wide
        };

        switch (operand->type)
        {
            case OperandType::None:
            {
            } break;
            case OperandType::Register8Bit:
            {
                resolved_operand.register_8_bit_id = operand->register_8_bit_id;
            } break;
            case OperandType::Register16Bit:
            {
                resolved_operand.register_16_bit_id = operand->register_16_bit_id;
            } break;
            case OperandType::MemoryAddress:
            {
                resolved_operand.memory_address = ResolveEffectiveAddress(&operand->memory_address, cpu_state);
            } break;
            case OperandType::Immediate:
            {
                resolved_operand.immediate_value = operand->immediate_value;
            } break;
            case OperandType::IPIncrement:
            {
                resolved_operand.ip_increment = operand->ip_increment;
            } break;
        }

        return resolved_operand;
    }
}
