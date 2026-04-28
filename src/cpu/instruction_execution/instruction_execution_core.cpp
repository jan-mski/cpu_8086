namespace cpu::instruction_execution::core
{
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::core::FlagId;
    using cpu::core::Register8BitId;
    using cpu::core::Register16BitId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Operand;
    using cpu::instruction::OperandType;
    using cpu::instruction::Mnemonic;
    using cpu::instruction_execution::resolution::ResolveEffectiveAddress;
    using cpu::instruction_execution::unary::ExecuteUnaryInstruction;
    using cpu::instruction_execution::unary::bitwise_not;
    using cpu::instruction_execution::binary::BinaryOp;
    using cpu::instruction_execution::binary::ExecuteBinaryInstruction;
    using cpu::instruction_execution::binary::noop;
    using cpu::instruction_execution::binary::add;
    using cpu::instruction_execution::binary::subtract;
    using cpu::instruction_execution::binary::bitwise_and;
    using cpu::instruction_execution::binary::bitwise_or;
    using cpu::instruction_execution::binary::bitwise_xor;
    using cpu::instruction_execution::binary::bitwise_shl;
    using cpu::instruction_execution::binary::bitwise_shr;
    using cpu::instruction_execution::binary::bitwise_sar;

    void UpdateFlag(uint16_t instruction_result, CpuState *cpu_state, FlagId flag_id)
    {
        switch (flag_id)
        {
            case FlagId::ZF:
            {
                cpu_state->SetFlagValue(FlagId::ZF, instruction_result == 0);
            } break;
            case FlagId::SF:
            {
                cpu_state->SetFlagValue(FlagId::SF, instruction_result & 0x8000);
            } break;
            default:
            {
            } break;
        }
    }

    template <std::same_as<FlagId>... FlagIds>
    void UpdateFlags(uint16_t instruction_result, CpuState *cpu_state, FlagIds... flag_ids)
    {
        (UpdateFlag(instruction_result, cpu_state, flag_ids), ...);
    }

    Operand CreateOperandImmediate(uint16_t immediate_value)
    {
        return {
            .type            = OperandType::Immediate,
            .immediate_value = immediate_value
        };
    }

    Operand CreateOperandRegister8Bit(Register8BitId register_id)
    {
        return {
            .type              = OperandType::Register8Bit,
            .register_8_bit_id = register_id
        };
    }

    Operand CreateOperandRegister16Bit(Register16BitId register_id)
    {
        return {
            .type               = OperandType::Register16Bit,
            .register_16_bit_id = register_id
        };
    }

    template <std::same_as<Register16BitId>... RegisterIds>
    Operand CreateOperandMemoryAddressFromRegisters(RegisterIds... register_ids)
    {
        return {
            .type           = OperandType::MemoryAddress,
            .memory_address = { .register_ids = { register_ids... } }
        };
    }

    Instruction CreateStoreOnStackInstruction(Instruction *instruction, Operand *source_operand)
    {
        Instruction store_value_on_stack = {
            .operands = {
                CreateOperandMemoryAddressFromRegisters(Register16BitId::SP),
                *source_operand
            },
            .is_wide = instruction->is_wide
        };

        return store_value_on_stack;
    }

    Instruction CreateLoadFromStackInstruction(Instruction *instruction, Operand *destination_operand)
    {
        Instruction load_value_from_stack = {
            .operands = {
                *destination_operand,
                CreateOperandMemoryAddressFromRegisters(Register16BitId::SP)
            },
            .is_wide = instruction->is_wide
        };
        return load_value_from_stack;
    }

    Instruction CreateUpdateIPInstruction(Instruction *instruction, Operand *update_operand)
    {
        Instruction set_ip_to_address = {
            .operands = {
                CreateOperandRegister16Bit(Register16BitId::IP),
                *update_operand
            },
            .is_wide = instruction->is_wide
        };

        return set_ip_to_address;
    }

    void ExecuteInstruction(Instruction *instruction, CpuState *cpu_state, Memory *memory)
    {
        switch (instruction->mnemonic)
        {
            case Mnemonic::MOV:
            {
                ExecuteBinaryInstruction(instruction, cpu_state, memory, true, noop);
            } break;
            case Mnemonic::ADD:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, true, add);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::INC:
            {
                Instruction inc_instruction = *instruction;
                inc_instruction.operands[1] = CreateOperandImmediate(1);

                uint16_t result = ExecuteBinaryInstruction(&inc_instruction, cpu_state, memory, true, add);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            }
            case Mnemonic::SUB:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, true, subtract);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::DEC:
            {
                Instruction dec_instruction = *instruction;
                dec_instruction.operands[1] = CreateOperandImmediate(1);

                uint16_t result = ExecuteBinaryInstruction(&dec_instruction, cpu_state, memory, true, subtract);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::CMP:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, false, subtract);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::NOT:
            {
                uint16_t result = ExecuteUnaryInstruction(instruction, cpu_state, memory, true, bitwise_not);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::AND:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, true, bitwise_and);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::OR:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, true, bitwise_or);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::XOR:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, true, bitwise_xor);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::TEST:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, false, bitwise_and);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::SHL_SAL:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, true, bitwise_shl);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::SHR:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, true, bitwise_shr);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::SAR:
            {
                uint16_t result = ExecuteBinaryInstruction(instruction, cpu_state, memory, true, bitwise_sar);
                UpdateFlags(result, cpu_state, FlagId::ZF, FlagId::SF);
            } break;
            case Mnemonic::JNE_JNZ:
            {
                if (cpu_state->GetFlagValue(FlagId::ZF) == 0)
                {
                    Instruction update_ip = CreateUpdateIPInstruction(instruction, &instruction->operands[0]);
                    ExecuteBinaryInstruction(&update_ip, cpu_state, memory, true, add);
                }
            } break;
            case Mnemonic::JMP:
            {
                Instruction update_ip = CreateUpdateIPInstruction(instruction, &instruction->operands[0]);
                BinaryOp op = instruction->operands[0].type == OperandType::IPIncrement ? add : noop;
                ExecuteBinaryInstruction(&update_ip, cpu_state, memory, true, op);
            } break;
            case Mnemonic::PUSH:
            {
                cpu_state->DecrementSP();

                Instruction store_value_on_stack = CreateStoreOnStackInstruction(
                    instruction,
                    &instruction->operands[0]);
                ExecuteBinaryInstruction(&store_value_on_stack, cpu_state, memory, true, noop);
            } break;
            case Mnemonic::POP:
            {
                Instruction load_value_from_stack = CreateLoadFromStackInstruction(
                    instruction,
                    &instruction->operands[0]);
                ExecuteBinaryInstruction(&load_value_from_stack, cpu_state, memory, true, noop);

                cpu_state->IncrementSP();
            } break;
            case Mnemonic::LEA:
            {
                uint16_t address = (uint16_t) ResolveEffectiveAddress(
                    &instruction->operands[1].memory_address,
                    cpu_state);

                Instruction lea_instruction = {
                    .operands = {
                        instruction->operands[0],
                        CreateOperandImmediate(address)
                    },
                };

                ExecuteBinaryInstruction(&lea_instruction, cpu_state, memory, true, noop);
            } break;
            case Mnemonic::CALL:
            {
                cpu_state->DecrementSP();

                Operand ip_operand = CreateOperandRegister16Bit(Register16BitId::IP);
                Instruction store_return_address_on_stack = CreateStoreOnStackInstruction(instruction, &ip_operand);
                ExecuteBinaryInstruction(&store_return_address_on_stack, cpu_state, memory, true, noop);

                Instruction update_ip = CreateUpdateIPInstruction(instruction, &instruction->operands[0]);
                BinaryOp op = instruction->operands[0].type == OperandType::IPIncrement ? add : noop;
                ExecuteBinaryInstruction(&update_ip, cpu_state, memory, true, op);
            } break;
            case Mnemonic::RET:
            {
                Operand ip_operand = CreateOperandRegister16Bit(Register16BitId::IP);
                Instruction load_return_address_from_stack = CreateLoadFromStackInstruction(instruction, &ip_operand);
                ExecuteBinaryInstruction(&load_return_address_from_stack, cpu_state, memory, true, noop);

                cpu_state->IncrementSP();
            } break;
            default:
            {
            } break;
        }
    }
}
