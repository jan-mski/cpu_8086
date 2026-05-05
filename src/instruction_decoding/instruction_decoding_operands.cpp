namespace instruction_decoding::operands
{
    namespace cpu = ::cpu;
    namespace ins = ::instruction;
    namespace dec_ctx = ::instruction_decoding::context;
    namespace dec_spx = ::instruction_decoding::specs;

    void SetDirectAddressFromDisplacement(ins::Operand* operand,
                                          dec_ctx::DecodingContext* decoding_context)
    {
        operand->memory_address.displacement = decoding_context->displacement;
    }

    void SetEffectiveAddress(ins::Operand* operand,
                             dec_ctx::DecodingContext* decoding_context)
    {
        cpu::Register16BitId effective_address_registers[][2] = {
            { cpu::Register16BitId_BX, cpu::Register16BitId_SI },
            { cpu::Register16BitId_BX, cpu::Register16BitId_DI },
            { cpu::Register16BitId_BP, cpu::Register16BitId_SI },
            { cpu::Register16BitId_BP, cpu::Register16BitId_DI },
            { cpu::Register16BitId_SI },
            { cpu::Register16BitId_DI },
            { cpu::Register16BitId_BP },
            { cpu::Register16BitId_BX }
        };

        for (U8 i = 0; i < ARRAY_SIZE(operand->memory_address.register_ids); ++i)
        {
            operand->memory_address.register_ids[i] = effective_address_registers[decoding_context->r_m][i];
        }
        operand->memory_address.displacement = decoding_context->displacement;
    }

    void SetRegister(ins::Operand* operand,
                     U8 w,
                     U8 reg_or_r_m)
    {
        if (w == 0)
        {
            cpu::Register8BitId registers_8_bit[] = {
                cpu::Register8BitId_AL, cpu::Register8BitId_CL, cpu::Register8BitId_DL,
                cpu::Register8BitId_BL, cpu::Register8BitId_AH, cpu::Register8BitId_CH,
                cpu::Register8BitId_DH, cpu::Register8BitId_BH
            };
            operand->type = ins::OperandType_Register8Bit;
            operand->register_8_bit_id = registers_8_bit[reg_or_r_m];
        }
        else
        {
            cpu::Register16BitId registers_16_bit[] = {
                cpu::Register16BitId_AX, cpu::Register16BitId_CX, cpu::Register16BitId_DX,
                cpu::Register16BitId_BX, cpu::Register16BitId_SP, cpu::Register16BitId_BP,
                cpu::Register16BitId_SI, cpu::Register16BitId_DI
            };
            operand->type = ins::OperandType_Register16Bit;
            operand->register_16_bit_id = registers_16_bit[reg_or_r_m];
        }
    }

    void SetMemoryOperandSizeProperties(ins::MemoryAddress* memory_address,
                                        dec_ctx::DecodingContext* decoding_context,
                                        bool is_any_operand_reg)
    {
        memory_address->is_operand_size_implicit = decoding_context->is_w_forced || is_any_operand_reg;
    }

    void DecodeOperandMemoryAddress(ins::Operand* operand,
                                    dec_ctx::DecodingContext* decoding_context)
    {
        operand->type = ins::OperandType_MemoryAddress;

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
            } break;
        }
    }

    bool DecodeOperandRegisterOrMemoryAddress(ins::Operand* operand,
                                              dec_ctx::DecodingContext* decoding_context)
    {
        bool is_memory_address = false;

        if (decoding_context->mod == 0b11)
        {
            SetRegister(operand, decoding_context->w, decoding_context->r_m);
        }
        else
        {
            DecodeOperandMemoryAddress(operand, decoding_context);
            is_memory_address = true;
        }

        return is_memory_address;
    }

    void DecodeOperandRegister(ins::Operand* operand,
                               dec_ctx::DecodingContext* decoding_context)
    {
        SetRegister(operand, decoding_context->w, decoding_context->reg);
    }

    void DecodeOperandSegmentRegister(ins::Operand* operand,
                                      dec_ctx::DecodingContext* decoding_context)
    {
        cpu::Register16BitId segment_registers[] = {
            cpu::Register16BitId_ES, cpu::Register16BitId_CS, cpu::Register16BitId_SS, cpu::Register16BitId_DS
        };

        operand->type = ins::OperandType_Register16Bit;
        operand->register_16_bit_id = segment_registers[decoding_context->sr];
    }

    void DecodeOperandImmediate(ins::Operand* operand,
                                dec_ctx::DecodingContext* decoding_context)
    {
        operand->type = ins::OperandType_Immediate;
        operand->immediate_value = decoding_context->data;
    }

    void DecodeOperandAccumulator(ins::Operand* operand,
                                  dec_ctx::DecodingContext* decoding_context)
    {
        if (decoding_context->w == 1)
        {
            operand->type = ins::OperandType_Register16Bit;
            operand->register_16_bit_id = cpu::Register16BitId_AX;
        }
        else
        {
            operand->type = ins::OperandType_Register8Bit;
            operand->register_8_bit_id = cpu::Register8BitId_AL;
        }
    }

    void DecodeOperandDataRegister(ins::Operand* operand,
                                   dec_ctx::DecodingContext* _)
    {
        operand->type = ins::OperandType_Register16Bit;
        operand->register_16_bit_id = cpu::Register16BitId_DX;
    }

    void DecodeOperandDirectAddress(ins::Operand* operand,
                                    dec_ctx::DecodingContext* decoding_context)
    {
        operand->type = ins::OperandType_MemoryAddress;
        operand->memory_address.displacement = decoding_context->addr;
    }

    void DecodeOperandIPIncrement(ins::Operand* operand,
                                  dec_ctx::DecodingContext* decoding_context)
    {
        operand->type = ins::OperandType_IPIncrement;
        operand->ip_increment = decoding_context->ip_increment;
    }

    void DecodeOperandShiftRotateCount(ins::Operand* operand,
                                       dec_ctx::DecodingContext* decoding_context)
    {
        if (decoding_context->v == 0)
        {
            operand->type = ins::OperandType_Immediate;
            operand->immediate_value = 1;
        }
        else
        {
            operand->type = ins::OperandType_Register8Bit;
            operand->register_8_bit_id = cpu::Register8BitId_CL;
        }
    }

    void DecodeBothRegisterOrMemoryOperands(ins::Instruction* instruction,
                                            dec_ctx::DecodingContext* decoding_context)
    {
        I8 memory_operand_idx = -1;

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

    void DecodeOperands(ins::Instruction* instruction,
                        dec_spx::OperandSpecType* operand_types,
                        dec_ctx::DecodingContext* decoding_context)
    {
        if (operand_types[0] == dec_spx::OperandSpecType_RegisterOrMemoryAddress &&
            operand_types[1] == dec_spx::OperandSpecType_RegisterOrMemoryAddress)
        {
            DecodeBothRegisterOrMemoryOperands(instruction, decoding_context);
            return;
        }

        bool is_any_operand_reg = false;
        I8 memory_operand_idx = -1;

        for (U8 i = 0; i < ins::OPERANDS_MAX_LEN; ++i)
        {
            dec_spx::OperandSpecType operand_type_spec = operand_types[i];

            if (operand_type_spec == dec_spx::OperandSpecType_None)
            {
                break;
            }

            switch (operand_type_spec)
            {
                case dec_spx::OperandSpecType_None:
                {
                } break;
                case dec_spx::OperandSpecType_Register:
                {
                    is_any_operand_reg = true;
                    DecodeOperandRegister(&instruction->operands[i], decoding_context);
                } break;
                case dec_spx::OperandSpecType_SegmentRegister:
                {
                    is_any_operand_reg = true;
                    DecodeOperandSegmentRegister(&instruction->operands[i], decoding_context);
                } break;
                case dec_spx::OperandSpecType_DataRegister:
                {
                    is_any_operand_reg = true;
                    DecodeOperandDataRegister(&instruction->operands[i], decoding_context);
                } break;
                case dec_spx::OperandSpecType_Accumulator:
                {
                    is_any_operand_reg = true;
                    DecodeOperandAccumulator(&instruction->operands[i], decoding_context);
                } break;
                case dec_spx::OperandSpecType_RegisterOrMemoryAddress:
                {
                    bool is_memory_operand = DecodeOperandRegisterOrMemoryAddress(
                        &instruction->operands[i],
                        decoding_context);
                    if (is_memory_operand)
                    {
                        memory_operand_idx = i;
                    }
                } break;
                case dec_spx::OperandSpecType_MemoryAddress:
                {
                    DecodeOperandMemoryAddress(&instruction->operands[i], decoding_context);
                    memory_operand_idx = i;
                } break;
                case dec_spx::OperandSpecType_DirectMemoryAddress:
                {
                    DecodeOperandDirectAddress(&instruction->operands[i], decoding_context);
                    memory_operand_idx = i;
                } break;
                case dec_spx::OperandSpecType_Immediate:
                {
                    DecodeOperandImmediate(&instruction->operands[i], decoding_context);
                } break;
                case dec_spx::OperandSpecType_IPIncrement:
                {
                    DecodeOperandIPIncrement(&instruction->operands[i], decoding_context);
                } break;
                case dec_spx::OperandSpecType_ShiftRotateCount:
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
