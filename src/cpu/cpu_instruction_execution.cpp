namespace cpu::instruction_execution
{
    using std::to_underlying;
    using cpu::core::CpuState;
    using cpu::core::RegisterId;
    using cpu::core::FlagId;
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
                    cpu_state->SetRegisterValue(register_id, immediate_value);
                } else if (instruction->operands[0].type == OperandType::Register &&
                           instruction->operands[1].type == OperandType::Register)
                {
                    RegisterId dst_register_id = instruction->operands[0].register_id;
                    RegisterId src_register_id = instruction->operands[1].register_id;
                    cpu_state->SetRegisterValue(dst_register_id, cpu_state->GetRegisterValue(src_register_id));
                }
            } break;
            case Mnemonic::ADD:
            {
                uint16_t result = 0;

                if (instruction->operands[0].type == OperandType::Register &&
                    instruction->operands[1].type == OperandType::Immediate)
                {
                    RegisterId register_id = instruction->operands[0].register_id;
                    uint16_t immediate_value = instruction->operands[1].immediate_value;
                    result = cpu_state->GetRegisterValue(register_id) + immediate_value;
                    cpu_state->SetRegisterValue(register_id, result);
                } else if (instruction->operands[0].type == OperandType::Register &&
                           instruction->operands[1].type == OperandType::Register)
                {
                    RegisterId dst_register_id = instruction->operands[0].register_id;
                    RegisterId src_register_id = instruction->operands[1].register_id;
                    result = cpu_state->GetRegisterValue(dst_register_id) +
                        cpu_state->GetRegisterValue(src_register_id);
                    cpu_state->SetRegisterValue(dst_register_id, result);
                }

                cpu_state->flags[to_underlying(FlagId::ZF)] = result == 0;
                cpu_state->flags[to_underlying(FlagId::SF)] = result & 0x8000;
            } break;
            case Mnemonic::SUB:
            {
                uint16_t result = 0;

                if (instruction->operands[0].type == OperandType::Register &&
                    instruction->operands[1].type == OperandType::Immediate)
                {
                    RegisterId register_id = instruction->operands[0].register_id;
                    uint16_t immediate_value = instruction->operands[1].immediate_value;
                    result = cpu_state->GetRegisterValue(register_id) - immediate_value;
                    cpu_state->SetRegisterValue(register_id, result);
                } else if (instruction->operands[0].type == OperandType::Register &&
                           instruction->operands[1].type == OperandType::Register)
                {
                    RegisterId dst_register_id = instruction->operands[0].register_id;
                    RegisterId src_register_id = instruction->operands[1].register_id;
                    result = cpu_state->GetRegisterValue(dst_register_id) -
                        cpu_state->GetRegisterValue(src_register_id);
                    cpu_state->SetRegisterValue(dst_register_id, result);
                }

                cpu_state->flags[to_underlying(FlagId::ZF)] = result == 0;
                cpu_state->flags[to_underlying(FlagId::SF)] = result & 0x8000;
            } break;
            case Mnemonic::CMP:
            {
                uint16_t result = 0;

                if (instruction->operands[0].type == OperandType::Register &&
                    instruction->operands[1].type == OperandType::Register)
                {
                    RegisterId dst_register_id = instruction->operands[0].register_id;
                    RegisterId src_register_id = instruction->operands[1].register_id;
                    result = cpu_state->GetRegisterValue(dst_register_id) -
                        cpu_state->GetRegisterValue(src_register_id);
                }

                cpu_state->flags[to_underlying(FlagId::ZF)] = result == 0;
                cpu_state->flags[to_underlying(FlagId::SF)] = result & 0x8000;
            } break;
            case Mnemonic::JNE_JNZ:
            {
                if (cpu_state->flags[to_underlying(FlagId::ZF)] == 0)
                {
                    cpu_state->IncrementInstructionPointer(instruction->operands[0].label_like_displacement);
                }
            } break;
            default:
            {

            } break;
        }
    }
}
