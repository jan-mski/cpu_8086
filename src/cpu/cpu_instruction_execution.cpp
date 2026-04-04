namespace cpu::instruction_execution
{
    using std::to_underlying;
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::core::RegisterId;
    using cpu::core::FlagId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Operand;
    using cpu::instruction::Mnemonic;
    using cpu::instruction::OperandType;
    using cpu::instruction::MemoryAddress;

    typedef uint16_t (* Op)(uint16_t, uint16_t);

    uint16_t add(uint16_t a, uint16_t b)
    {
        return a + b;
    }

    uint16_t subtract(uint16_t a, uint16_t b)
    {
        return a - b;
    }

    uint32_t ResolveEffectiveAddress(MemoryAddress *memory_address, CpuState *cpu_state)
    {
        int32_t effective_address = memory_address->displacement;
        for (uint8_t i = 0; memory_address->register_ids[i] != RegisterId::None; ++i)
        {
            effective_address += cpu_state->GetRegisterValue(memory_address->register_ids[i]);
        }

        return (uint32_t) effective_address;
    }

    int32_t GetOperandValue(Operand *operand, CpuState *cpu_state, Memory *memory)
    {
        switch (operand->type)
        {
            case OperandType::None:
            {
            } break;
            case OperandType::Register:
            {
                return cpu_state->GetRegisterValue(operand->register_id);
            } break;
            case OperandType::Immediate:
            {
                return operand->immediate_value;
            } break;
            case OperandType::MemoryAddress:
            {
                uint32_t effective_address = ResolveEffectiveAddress(&operand->memory_address, cpu_state);

                return operand->memory_address.operand_size_bytes == 2
                    ? memory->ReadWord(effective_address)
                    : memory->ReadByte(effective_address);
            } break;
            case OperandType::LabelLikeDisplacement:
            {
                return operand->label_like_displacement;
            } break;
        }

        return 0;
    }

    uint16_t ExecuteInstruction(Operand *operand_1,
                                Operand *operand_2,
                                CpuState *cpu_state,
                                Memory *memory,
                                bool do_set_result,
                                Op op = nullptr)
    {
        int32_t operand_2_value = GetOperandValue(operand_2, cpu_state, memory);
        uint16_t result = operand_2_value;

        if (operand_1->type == OperandType::Register)
        {
            result = op != nullptr
                         ? op(cpu_state->GetRegisterValue(operand_1->register_id), operand_2_value)
                         : operand_2_value;

            if (do_set_result)
            {
                cpu_state->SetRegisterValue(operand_1->register_id, result);
            }
        }
        else if (operand_1->type == OperandType::MemoryAddress)
        {
            uint32_t effective_address = ResolveEffectiveAddress(&operand_1->memory_address, cpu_state);

            if (op != nullptr)
            {
                uint8_t operand_1_value = memory->ReadByte(effective_address);
                result = op(operand_1_value, operand_2_value);
            }
            else
            {
                result = operand_2_value;
            }

            if (do_set_result)
            {
                operand_1->memory_address.operand_size_bytes == 2
                    ? memory->WriteWord(effective_address, result)
                    : memory->WriteByte(effective_address, result);
            }
        }

        return result;
    }

    void ExecuteInstruction(Instruction *instruction, CpuState *cpu_state, Memory *memory)
    {
        Operand *operand_1 = &instruction->operands[0];
        Operand *operand_2 = &instruction->operands[1];

        switch (instruction->mnemonic)
        {
            case Mnemonic::MOV:
            {
                ExecuteInstruction(operand_1, operand_2, cpu_state, memory, true, nullptr);
            } break;
            case Mnemonic::ADD:
            {
                uint16_t result = ExecuteInstruction(operand_1, operand_2, cpu_state, memory, true, add);
                cpu_state->flags[to_underlying(FlagId::ZF)] = result == 0;
                cpu_state->flags[to_underlying(FlagId::SF)] = result & 0x8000;
            } break;
            case Mnemonic::SUB:
            {
                uint16_t result = ExecuteInstruction(operand_1, operand_2, cpu_state, memory, true, subtract);
                cpu_state->flags[to_underlying(FlagId::ZF)] = result == 0;
                cpu_state->flags[to_underlying(FlagId::SF)] = result & 0x8000;
            } break;
            case Mnemonic::CMP:
            {
                uint16_t result = ExecuteInstruction(operand_1, operand_2, cpu_state, memory, false, subtract);
                cpu_state->flags[to_underlying(FlagId::ZF)] = result == 0;
                cpu_state->flags[to_underlying(FlagId::SF)] = result & 0x8000;
            } break;
            case Mnemonic::JNE_JNZ:
            {
                if (cpu_state->flags[to_underlying(FlagId::ZF)] == 0)
                {
                    cpu_state->IncrementInstructionPointer(operand_1->label_like_displacement);
                }
            } break;
            default:
            {
            } break;
        }
    }
}
