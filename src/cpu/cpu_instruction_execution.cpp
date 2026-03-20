namespace cpu::instruction_execution
{
    using cpu::state::CpuState;
    using cpu::state::RegisterId;
    using cpu::state::FlagId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Mnemonic;
    using cpu::instruction::OperandType;

    void ExecuteInstruction(Instruction *instruction, CpuState *cpu_state)
    {
        switch (instruction->mnemonic)
        {
            case Mnemonic::MOV:
            {
                if (instruction->operands[0].type == OperandType::Register &&
                    instruction->operands[1].type == OperandType::Immediate)
                {
                    RegisterId register_id = instruction->operands[0].register_id;
                    uint16_t immediate_value = instruction->operands[1].immediate_value;
                    SetRegisterValue(cpu_state->registers, register_id, immediate_value);
                } else if (instruction->operands[0].type == OperandType::Register &&
                           instruction->operands[1].type == OperandType::Register)
                {
                    RegisterId dst_register_id = instruction->operands[0].register_id;
                    RegisterId src_register_id = instruction->operands[1].register_id;
                    SetRegisterValue(cpu_state->registers, dst_register_id, GetRegisterValue(cpu_state->registers, src_register_id));
                }
            }
            break;
            case Mnemonic::ADD:
            {
                uint16_t result = 0;

                if (instruction->operands[0].type == OperandType::Register &&
                    instruction->operands[1].type == OperandType::Immediate)
                {
                    RegisterId register_id = instruction->operands[0].register_id;
                    uint16_t immediate_value = instruction->operands[1].immediate_value;
                    result = GetRegisterValue(cpu_state->registers, register_id) + immediate_value;
                    SetRegisterValue(cpu_state->registers, register_id, result);
                } else if (instruction->operands[0].type == OperandType::Register &&
                           instruction->operands[1].type == OperandType::Register)
                {
                    RegisterId dst_register_id = instruction->operands[0].register_id;
                    RegisterId src_register_id = instruction->operands[1].register_id;
                    result = GetRegisterValue(cpu_state->registers, dst_register_id) +
                        GetRegisterValue(cpu_state->registers, src_register_id);
                    SetRegisterValue(cpu_state->registers, dst_register_id, result);
                }

                cpu_state->flags[FlagId::FlagId_ZF] = result == 0;
                cpu_state->flags[FlagId::FlagId_SF] = result & 0x8000;
            }
            break;
            case Mnemonic::SUB:
            {
                uint16_t result = 0;

                if (instruction->operands[0].type == OperandType::Register &&
                    instruction->operands[1].type == OperandType::Immediate)
                {
                    RegisterId register_id = instruction->operands[0].register_id;
                    uint16_t immediate_value = instruction->operands[1].immediate_value;
                    result = GetRegisterValue(cpu_state->registers, register_id) - immediate_value;
                    SetRegisterValue(cpu_state->registers, register_id, result);
                } else if (instruction->operands[0].type == OperandType::Register &&
                           instruction->operands[1].type == OperandType::Register)
                {
                    RegisterId dst_register_id = instruction->operands[0].register_id;
                    RegisterId src_register_id = instruction->operands[1].register_id;
                    result = GetRegisterValue(cpu_state->registers, dst_register_id) -
                        GetRegisterValue(cpu_state->registers, src_register_id);
                    SetRegisterValue(cpu_state->registers, dst_register_id, result);
                }

                cpu_state->flags[FlagId::FlagId_ZF] = result == 0;
                cpu_state->flags[FlagId::FlagId_SF] = result & 0x8000;
            }
            break;
            case Mnemonic::CMP:
            {
                uint16_t result = 0;

                if (instruction->operands[0].type == OperandType::Register &&
                    instruction->operands[1].type == OperandType::Register)
                {
                    RegisterId dst_register_id = instruction->operands[0].register_id;
                    RegisterId src_register_id = instruction->operands[1].register_id;
                    result = GetRegisterValue(cpu_state->registers, dst_register_id) -
                        GetRegisterValue(cpu_state->registers, src_register_id);
                }

                cpu_state->flags[FlagId::FlagId_ZF] = result == 0;
                cpu_state->flags[FlagId::FlagId_SF] = result & 0x8000;
            }
            break;
            default:
            {
            }
            break;
        }
    }
}
