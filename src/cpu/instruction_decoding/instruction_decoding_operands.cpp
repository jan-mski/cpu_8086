namespace cpu::instruction_decoding::operands
{
    using cpu::core::Register8BitId;
    using cpu::core::Register16BitId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Operand;
    using cpu::instruction::OperandType;
    using cpu::instruction::MemoryAddress;
    using cpu::instruction_decoding::specs::OperandSpecType;
    using cpu::instruction_decoding::context::DecodingContext;

    void SetDirectAddressFromDisplacement(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::MemoryAddress;
        operand->memory_address.displacement = decoding_context->displacement;
    }

    void SetEffectiveAddress(Operand *operand, DecodingContext *decoding_context)
    {
        Register16BitId effective_address_registers[][2] = {
            {Register16BitId::BX, Register16BitId::SI},
            {Register16BitId::BX, Register16BitId::DI},
            {Register16BitId::BP, Register16BitId::SI},
            {Register16BitId::BP, Register16BitId::DI},
            {Register16BitId::SI},
            {Register16BitId::DI},
            {Register16BitId::BP},
            {Register16BitId::BX}
        };

        operand->type = OperandType::MemoryAddress;
        for (uint8_t i = 0; i < ARRAY_SIZE(operand->memory_address.register_ids); ++i)
        {
            operand->memory_address.register_ids[i] = effective_address_registers[decoding_context->r_m][i];
        }
        operand->memory_address.displacement = decoding_context->displacement;
    }

    void SetRegister(Operand *operand, uint8_t w, uint8_t reg_or_r_m)
    {
        if (w == 0)
        {
            Register8BitId registers_8_bit[] = {
                Register8BitId::AL, Register8BitId::CL, Register8BitId::DL,
                Register8BitId::BL, Register8BitId::AH, Register8BitId::CH,
                Register8BitId::DH, Register8BitId::BH
            };
            operand->type = OperandType::Register8Bit;
            operand->register_8_bit_id = registers_8_bit[reg_or_r_m];
        }
        else
        {
            Register16BitId registers_16_bit[] = {
                Register16BitId::AX, Register16BitId::CX, Register16BitId::DX,
                Register16BitId::BX, Register16BitId::SP, Register16BitId::BP,
                Register16BitId::SI, Register16BitId::DI
            };
            operand->type = OperandType::Register16Bit;
            operand->register_16_bit_id = registers_16_bit[reg_or_r_m];
        }
    }

    void SetMemoryOperandSizeProperties(MemoryAddress *memory_address,
                                        DecodingContext *decoding_context,
                                        bool is_any_operand_reg)
    {
        memory_address->is_operand_size_implicit = decoding_context->is_w_forced || is_any_operand_reg;
    }

    bool DecodeOperandRegisterOrMemoryAddress(Operand *operand, DecodingContext *decoding_context)
    {
        switch (decoding_context->mod)
        {
            case 0b00:
            {
                if (decoding_context->r_m == 0b110)
                {
                    SetDirectAddressFromDisplacement(operand, decoding_context);
                }
                else
                {
                    SetEffectiveAddress(operand, decoding_context);
                }
            } break;
            case 0b01:
            case 0b10:
            {
                SetEffectiveAddress(operand, decoding_context);
            } break;
            default:
            {
                SetRegister(operand, decoding_context->w, decoding_context->r_m);

                return false;
            } break;
        }

        return true;
    }

    void DecodeOperandRegister(Operand *operand, DecodingContext *decoding_context)
    {
        SetRegister(operand, decoding_context->w, decoding_context->reg);
    }

    void DecodeOperandSegmentRegister(Operand *operand, DecodingContext *decoding_context)
    {
        Register16BitId segment_registers[] = {
            Register16BitId::ES, Register16BitId::CS, Register16BitId::SS, Register16BitId::DS
        };

        operand->type = OperandType::Register16Bit;
        operand->register_16_bit_id = segment_registers[decoding_context->sr];
    }

    void DecodeOperandImmediate(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::Immediate;
        operand->immediate_value = decoding_context->data;
    }

    void DecodeOperandAccumulator(Operand *operand, DecodingContext *decoding_context)
    {
        if (decoding_context->w == 1)
        {
            operand->type = OperandType::Register16Bit;
            operand->register_16_bit_id = Register16BitId::AX;
        }
        else
        {
            operand->type = OperandType::Register8Bit;
            operand->register_8_bit_id = Register8BitId::AL;
        }
    }

    void DecodeOperandDataRegister(Operand *operand, DecodingContext *_)
    {
        operand->type = OperandType::Register16Bit;
        operand->register_16_bit_id = Register16BitId::DX;
    }

    void DecodeOperandDirectAddress(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::MemoryAddress;
        operand->memory_address.displacement = decoding_context->addr;
    }

    void DecodeOperandIPIncrement(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::IPIncrement;
        operand->ip_increment = decoding_context->ip_increment;
    }

    void DecodeOperandShiftRotateCount(Operand *operand, DecodingContext *decoding_context)
    {
        if (decoding_context->v == 0)
        {
            operand->type = OperandType::Immediate;
            operand->immediate_value = 1;
        }
        else
        {
            operand->type = OperandType::Register8Bit;
            operand->register_8_bit_id = Register8BitId::CL;
        }
    }

    void DecodeBothRegisterOrMemoryOperands(Instruction *instruction, DecodingContext *decoding_context)
    {
        int8_t memory_operand_idx = -1;

        if (decoding_context->d == 0)
        {
            bool is_memory_operand = DecodeOperandRegisterOrMemoryAddress(
                &instruction->operands[0],
                decoding_context);
            if (is_memory_operand)
            {
                memory_operand_idx = 0;
            }

            DecodeOperandRegister(&instruction->operands[1], decoding_context);
        }
        else
        {
            DecodeOperandRegister(&instruction->operands[0], decoding_context);

            bool is_memory_operand = DecodeOperandRegisterOrMemoryAddress(
                &instruction->operands[1],
                decoding_context);
            if (is_memory_operand)
            {
                memory_operand_idx = 1;
            }
        }

        if (memory_operand_idx != -1)
        {
            SetMemoryOperandSizeProperties(
                &instruction->operands[memory_operand_idx].memory_address,
                decoding_context,
                true);
        }
    }

    void DecodeOperands(Instruction *instruction,
                        OperandSpecType *operand_types,
                        uint8_t num_operands,
                        DecodingContext *decoding_context)
    {
        if (num_operands == 2 &&
            operand_types[0] == OperandSpecType::RegisterOrMemoryAddress &&
            operand_types[1] == OperandSpecType::RegisterOrMemoryAddress)
        {
            DecodeBothRegisterOrMemoryOperands(instruction, decoding_context);
            return;
        }

        bool is_any_operand_reg = false;
        int8_t memory_operand_idx = -1;

        for (uint8_t i = 0; i < num_operands; ++i)
        {
            OperandSpecType operand_type_spec = operand_types[i];

            if (operand_type_spec == OperandSpecType::None)
            {
                break;
            }

            switch (operand_type_spec)
            {
                case OperandSpecType::None:
                {
                } break;
                case OperandSpecType::Register:
                {
                    is_any_operand_reg = true;
                    DecodeOperandRegister(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::SegmentRegister:
                {
                    is_any_operand_reg = true;
                    DecodeOperandSegmentRegister(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::DataRegister:
                {
                    is_any_operand_reg = true;
                    DecodeOperandDataRegister(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::Accumulator:
                {
                    is_any_operand_reg = true;
                    DecodeOperandAccumulator(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::RegisterOrMemoryAddress:
                {
                    bool is_memory_operand = DecodeOperandRegisterOrMemoryAddress(
                        &instruction->operands[i],
                        decoding_context);
                    if (is_memory_operand)
                    {
                        memory_operand_idx = i;
                    }
                } break;
                case OperandSpecType::DirectMemoryAddress:
                {
                    DecodeOperandDirectAddress(&instruction->operands[i], decoding_context);
                    memory_operand_idx = i;
                } break;
                case OperandSpecType::Immediate:
                {
                    DecodeOperandImmediate(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::IPIncrement:
                {
                    DecodeOperandIPIncrement(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::ShiftRotateCount:
                {
                    DecodeOperandShiftRotateCount(&instruction->operands[i], decoding_context);
                } break;
            }
        }

        if (memory_operand_idx != -1)
        {
            SetMemoryOperandSizeProperties(
                &instruction->operands[memory_operand_idx].memory_address,
                decoding_context,
                is_any_operand_reg);
        }
    }
}
