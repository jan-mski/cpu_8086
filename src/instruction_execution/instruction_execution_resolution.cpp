namespace instruction_execution::resolution
{
    namespace mem = ::memory;
    namespace cpu = ::cpu;
    namespace ins = ::instruction;

    mem::Address ResolveEffectiveAddress(ins::MemoryAddress* memory_address,
                                         cpu::CpuState* cpu_state)
    {
        I32 effective_address = memory_address->displacement;
        for (U8 i = 0; memory_address->register_ids[i] != cpu::Register16BitId_None; ++i)
        {
            effective_address += cpu::GetRegisterValue(cpu_state, memory_address->register_ids[i]);
        }

        return (mem::Address) effective_address;
    }

    I32 GetResolvedOperandValue(ResolvedOperand* resolved_operand,
                                bool is_instruction_wide,
                                cpu::CpuState* cpu_state,
                                mem::Memory* memory)
    {
        I32 value = 0;

        ins::Operand* operand = resolved_operand->operand;

        switch (operand->type)
        {
            case ins::OperandType_None:
            {
            } break;
            case ins::OperandType_Register8Bit:
            {
                value = cpu::GetRegisterValue(cpu_state, operand->register_8_bit_id);
            } break;
            case ins::OperandType_Register16Bit:
            {
                value = cpu::GetRegisterValue(cpu_state, operand->register_16_bit_id);
            } break;
            case ins::OperandType_Immediate:
            {
                value = operand->immediate_value;
            } break;
            case ins::OperandType_MemoryAddress:
            {
                value = is_instruction_wide
                            ? mem::ReadWord(memory, resolved_operand->resolved_ea)
                            : mem::ReadByte(memory, resolved_operand->resolved_ea);
            } break;
            case ins::OperandType_IPIncrement:
            {
                value = operand->ip_increment;
            } break;
        }

        return value;
    }

    void SetResolvedOperandValue(ResolvedOperand* resolved_operand,
                                 bool is_instruction_wide,
                                 U16 value,
                                 cpu::CpuState* cpu_state,
                                 mem::Memory* memory)
    {
        ins::Operand* operand = resolved_operand->operand;

        switch (operand->type)
        {
            case ins::OperandType_None:
            case ins::OperandType_Immediate:
            case ins::OperandType_IPIncrement:
            {
            } break;
            case ins::OperandType_Register8Bit:
            {
                cpu::SetRegisterValue(cpu_state, operand->register_8_bit_id, (U8) value);
            } break;
            case ins::OperandType_Register16Bit:
            {
                cpu::SetRegisterValue(cpu_state, operand->register_16_bit_id, value);
            } break;
            case ins::OperandType_MemoryAddress:
            {
                is_instruction_wide
                    ? mem::WriteWord(memory, resolved_operand->resolved_ea, value)
                    : mem::WriteByte(memory, resolved_operand->resolved_ea, (U8) value);
            } break;
        }
    }

    ResolvedInstruction ResolveInstruction(ins::Operand* operands,
                                           U8 num_operands,
                                           bool is_wide,
                                           cpu::CpuState* cpu_state)
    {
        ResolvedInstruction resolved_instruction = { .is_wide = is_wide };

        for (U8 i = 0; i < num_operands; ++i)
        {
            ins::Operand* operand = &operands[i];

            ResolvedOperand resolved_operand = { operand };

            if (operand->type == ins::OperandType_MemoryAddress)
            {
                mem::Address resolved_ea = ResolveEffectiveAddress(&operand->memory_address, cpu_state);
                resolved_operand.resolved_ea = resolved_ea;
                resolved_instruction.resolved_ea = resolved_ea;
            }

            resolved_instruction.operands[i] = resolved_operand;
        }

        return resolved_instruction;
    }
}
