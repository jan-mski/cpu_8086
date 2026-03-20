namespace cpu::instruction_decoding::context
{
    using cpu::instruction_input::InstructionInput;
    using cpu::instruction_input::ReadByte;

    size_t ReadNextByte(InstructionDecodeContext *decoding_context,
                        InstructionInput *instruction_input)
    {
        size_t num_bytes_read = ReadByte(decoding_context->bytes + decoding_context->num_bytes_read, instruction_input);
        decoding_context->num_bytes_read += num_bytes_read;

        return num_bytes_read;
    }

    void ReadBytesUpToIdx(InstructionDecodeContext *decoding_context,
                          uint8_t byte_idx,
                          InstructionInput *instruction_input)
    {
        while (decoding_context->num_bytes_read <= byte_idx)
        {
            ReadNextByte(decoding_context, instruction_input);
        }
    }
}

namespace cpu::instruction_decoding::fields
{
    using cpu::instruction_input::InstructionInput;
    using cpu::instruction_input::ReadByte;
    using cpu::instruction_decoding::context::InstructionDecodeContext;
    using cpu::instruction_decoding::context::ReadNextByte;
    using cpu::instruction_decoding::context::ReadBytesUpToIdx;

    uint8_t DecodeField(FieldSpec field_spec,
                        uint8_t byte_idx,
                        InstructionDecodeContext *decoding_context,
                        InstructionInput *instruction_input)
    {
        ReadBytesUpToIdx(decoding_context, byte_idx, instruction_input);

        return field_spec.is_forced
                   ? field_spec.forced_value
                   : (decoding_context->bytes[byte_idx] >> field_spec.bit_shift) & field_spec.bit_mask;
    }

    uint8_t DecodeByte(InstructionDecodeContext *decoding_context,
                       InstructionInput *instruction_input)
    {
        ReadNextByte(decoding_context, instruction_input);

        return decoding_context->bytes[decoding_context->num_bytes_read - 1];
    }

    int32_t DecodeHighByte(int32_t low_byte_value,
                           InstructionDecodeContext *decoding_context,
                           InstructionInput *instruction_input)
    {
        return DecodeByte(decoding_context, instruction_input) << 8 | low_byte_value;
    }

    int32_t DecodeDataHighByte(InstructionDecodeContext *decoding_context,
                               InstructionInput *instruction_input)
    {
        return (decoding_context->w == 1 && decoding_context->s == 0)
                   ? DecodeHighByte(decoding_context->data, decoding_context, instruction_input)
                   : decoding_context->data;
    }

    int32_t DecodeAddrHighByte(InstructionDecodeContext *decoding_context,
                               InstructionInput *instruction_input)
    {
        return decoding_context->w == 1
                   ? DecodeHighByte(decoding_context->addr, decoding_context, instruction_input)
                   : decoding_context->addr;
    }

    int32_t DecodeDisplacement8Bit(InstructionDecodeContext *decoding_context,
                                   InstructionInput *instruction_input)
    {
        int32_t byte_value = DecodeByte(decoding_context, instruction_input);

        return (byte_value >> 7) & 0b1
                   ? -((byte_value ^ 0b11111111) + 0b1) // negative number, so we do two's complement
                   : byte_value;
    }

    int32_t DecodeDisplacement16Bit(InstructionDecodeContext *decoding_context,
                                    InstructionInput *instruction_input)
    {
        int32_t low_byte_value = DecodeByte(decoding_context, instruction_input);

        return DecodeHighByte(low_byte_value, decoding_context, instruction_input);
    }

    int32_t DecodeDisplacement(InstructionDecodeContext *decoding_context,
                               InstructionInput *instruction_input)
    {
        switch (decoding_context->mod)
        {
            case 0b00:
            {
                if (decoding_context->r_m == 0b110)
                {
                    return DecodeDisplacement16Bit(decoding_context, instruction_input);
                }
            } break;
            case 0b01:
            {
                return DecodeDisplacement8Bit(decoding_context, instruction_input);
            } break;
            case 0b10:
            {
                return DecodeDisplacement16Bit(decoding_context, instruction_input);
            } break;
            default:
            {
            } break;
        }

        return 0;
    }

    void DecodeByteFields(FieldSpec *byte_field_specs,
                          uint8_t byte_idx,
                          InstructionDecodeContext *decoding_context,
                          InstructionInput *instruction_input)
    {
        for (uint8_t i = 0; i < BYTE_FIELDS_MAX_LEN; ++i)
        {
            FieldSpec field_spec = byte_field_specs[i];

            if (field_spec.type == FieldSpecType::None)
            {
                break;
            }

            switch (field_spec.type)
            {
                case FieldSpecType::None:
                {
                } break;
                case FieldSpecType::D:
                {
                    decoding_context->d = DecodeField(field_spec, byte_idx, decoding_context, instruction_input);
                } break;
                case FieldSpecType::S:
                {
                    decoding_context->s = DecodeField(field_spec, byte_idx, decoding_context, instruction_input);
                } break;
                case FieldSpecType::V:
                {
                    decoding_context->v = DecodeField(field_spec, byte_idx, decoding_context, instruction_input);
                } break;
                case FieldSpecType::W:
                {
                    decoding_context->w = DecodeField(field_spec, byte_idx, decoding_context, instruction_input);
                } break;
                case FieldSpecType::MOD:
                {
                    decoding_context->mod = DecodeField(field_spec, byte_idx, decoding_context, instruction_input);
                } break;
                case FieldSpecType::RM:
                {
                    decoding_context->r_m = DecodeField(field_spec, byte_idx, decoding_context, instruction_input);
                } break;
                case FieldSpecType::REG:
                {
                    decoding_context->reg = DecodeField(field_spec, byte_idx, decoding_context, instruction_input);
                } break;
                case FieldSpecType::SR:
                {
                    decoding_context->sr = DecodeField(field_spec, byte_idx, decoding_context, instruction_input);
                } break;
                case FieldSpecType::DISP_8:
                {
                    decoding_context->displacement = DecodeDisplacement8Bit(decoding_context, instruction_input);
                } break;
                case FieldSpecType::DISP:
                {
                    decoding_context->displacement = DecodeDisplacement(decoding_context, instruction_input);
                } break;
                case FieldSpecType::DATA_8:
                {
                    decoding_context->data = DecodeByte(decoding_context, instruction_input);
                } break;
                case FieldSpecType::DATA_LO:
                {
                    decoding_context->data = DecodeByte(decoding_context, instruction_input);
                } break;
                case FieldSpecType::DATA_HI:
                {
                    decoding_context->data = DecodeDataHighByte(decoding_context, instruction_input);
                } break;
                case FieldSpecType::ADDR_LO:
                {
                    decoding_context->addr = DecodeByte(decoding_context, instruction_input);
                } break;
                case FieldSpecType::ADDR_HI:
                {
                    decoding_context->addr = DecodeAddrHighByte(decoding_context, instruction_input);
                } break;
                case FieldSpecType::OpcodeExtension:
                {
                    decoding_context->opcode_extension = DecodeField(
                        field_spec,
                        byte_idx,
                        decoding_context,
                        instruction_input);
                } break;
            }
        }
    }
}

namespace cpu::instruction_decoding::operands
{
    using cpu::state::RegisterId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Operand;
    using cpu::instruction::OperandType;
    using cpu::instruction::MemoryAddressQualifier;
    using cpu::instruction_decoding::context::InstructionDecodeContext;

    void SetDirectAddressFromDisplacement(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        operand->type = OperandType::MemoryAddress;
        operand->memory_address.direct = true;
        operand->memory_address.displacement = decoding_context->displacement;
    }

    void SetEffectiveAddress(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        RegisterId effective_address_registers[][2] = {
            {RegisterId::RegisterId_BX, RegisterId::RegisterId_SI},
            {RegisterId::RegisterId_BX, RegisterId::RegisterId_DI},
            {RegisterId::RegisterId_BP, RegisterId::RegisterId_SI},
            {RegisterId::RegisterId_BP, RegisterId::RegisterId_DI},
            {RegisterId::RegisterId_SI},
            {RegisterId::RegisterId_DI},
            {RegisterId::RegisterId_BP},
            {RegisterId::RegisterId_BX}
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
        RegisterId registers_by_w[][8] = {
            {
                RegisterId::RegisterId_AL, RegisterId::RegisterId_CL, RegisterId::RegisterId_DL,
                RegisterId::RegisterId_BL, RegisterId::RegisterId_AH, RegisterId::RegisterId_CH,
                RegisterId::RegisterId_DH, RegisterId::RegisterId_BH
            },
            {
                RegisterId::RegisterId_AX, RegisterId::RegisterId_CX, RegisterId::RegisterId_DX,
                RegisterId::RegisterId_BX, RegisterId::RegisterId_SP, RegisterId::RegisterId_BP,
                RegisterId::RegisterId_SI, RegisterId::RegisterId_DI
            }
        };

        operand->type = OperandType::Register;
        operand->register_id = registers_by_w[w][reg_or_r_m];
    }

    void DecodeOperandRegisterOrMemoryAddress(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        switch (decoding_context->mod)
        {
            case 0b00:
            {
                if (decoding_context->r_m == 0b110)
                {
                    SetDirectAddressFromDisplacement(operand, decoding_context);
                } else
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
                return;
            } break;
        }

        MemoryAddressQualifier qualifier = decoding_context->w == 1
                                               ? MemoryAddressQualifier::Word
                                               : MemoryAddressQualifier::Byte;
        operand->memory_address.qualifier = qualifier;
    }

    void DecodeOperandRegister(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        SetRegister(operand, decoding_context->w, decoding_context->reg);
    }

    void DecodeOperandSegmentRegister(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        RegisterId segment_registers[] = {
            RegisterId::RegisterId_ES, RegisterId::RegisterId_CS, RegisterId::RegisterId_SS, RegisterId::RegisterId_DS
        };

        operand->type = OperandType::Register;
        operand->register_id = segment_registers[decoding_context->sr];
    }

    void DecodeOperandImmediate(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        operand->type = OperandType::Immediate;
        operand->immediate_value = decoding_context->data;
    }

    void DecodeOperandAccumulator(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        operand->type = OperandType::Register;
        operand->register_id = decoding_context->w == 1
                                   ? RegisterId::RegisterId_AX
                                   : RegisterId::RegisterId_AL;
    }

    void DecodeOperandDataRegister(Operand *operand, InstructionDecodeContext *_)
    {
        operand->type = OperandType::Register;
        operand->register_id = RegisterId::RegisterId_DX;
    }

    void DecodeOperandDirectAddress(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        operand->type = OperandType::MemoryAddress;
        operand->memory_address.direct = true;
        operand->memory_address.displacement = decoding_context->addr;
    }

    void DecodeOperandLabelLikeDisplacement(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        operand->type = OperandType::LabelLikeDisplacement;
        operand->label_like_displacement = decoding_context->displacement;
    }

    void DecodeOperandShiftRotateCount(Operand *operand, InstructionDecodeContext *decoding_context)
    {
        if (decoding_context->v == 0)
        {
            operand->type = OperandType::Immediate;
            operand->immediate_value = 1;
        } else
        {
            operand->type = OperandType::Register;
            operand->register_id = RegisterId::RegisterId_CL;
        }
    }

    void DecodeOperands(Instruction *instruction,
                        OperandSpecType *operand_types,
                        uint8_t num_operands,
                        InstructionDecodeContext *decoding_context)
    {
        if (num_operands == 2 &&
            operand_types[0] == OperandSpecType::RegisterOrMemoryAddress &&
            operand_types[1] == OperandSpecType::RegisterOrMemoryAddress)
        {
            if (decoding_context->d == 0)
            {
                DecodeOperandRegisterOrMemoryAddress(&instruction->operands[0], decoding_context);
                DecodeOperandRegister(&instruction->operands[1], decoding_context);
            } else
            {
                DecodeOperandRegister(&instruction->operands[0], decoding_context);
                DecodeOperandRegisterOrMemoryAddress(&instruction->operands[1], decoding_context);
            }
            return;
        }

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
                    DecodeOperandRegister(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::SegmentRegister:
                {
                    DecodeOperandSegmentRegister(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::DataRegister:
                {
                    DecodeOperandDataRegister(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::RegisterOrMemoryAddress:
                {
                    DecodeOperandRegisterOrMemoryAddress(
                        &instruction->operands[i],
                        decoding_context);
                } break;
                case OperandSpecType::DirectMemoryAddress:
                {
                    DecodeOperandDirectAddress(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::Accumulator:
                {
                    DecodeOperandAccumulator(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::Immediate:
                {
                    DecodeOperandImmediate(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::LabelLikeDisplacement:
                {
                    DecodeOperandLabelLikeDisplacement(&instruction->operands[i], decoding_context);
                } break;
                case OperandSpecType::ShiftRotateCount:
                {
                    DecodeOperandShiftRotateCount(&instruction->operands[i], decoding_context);
                } break;
            }
        }
    }
}

namespace cpu::instruction_decoding::core
{
    using cpu::instruction::Instruction;
    using cpu::instruction_input::InstructionInput;
    using cpu::instruction_decoding::context::InstructionDecodeContext;
    using cpu::instruction_decoding::fields::DecodeByteFields;
    using cpu::instruction_decoding::operands::DecodeOperands;
    using cpu::instruction_decoding::specs::InstructionSpec;
    using cpu::instruction_decoding::specs::InstructionSpecBody;
    using cpu::instruction_decoding::specs::InstructionSpecType;
    using cpu::instruction_decoding::specs::OPCODE_EXT_BYTE_FIELDS;
    using cpu::instruction_decoding::specs::INSTRUCTION_SPECS;

    Instruction DecodeInstruction(InstructionSpec *instruction_spec,
                                  InstructionDecodeContext *decoding_context,
                                  InstructionInput *instruction_input)
    {
        Instruction instruction = {};
        InstructionSpecBody *instruction_spec_body = 0;

        switch (instruction_spec->type)
        {
            case InstructionSpecType::None:
            {
                return instruction;
            } break;
            case InstructionSpecType::Regular:
            {
                instruction_spec_body = &instruction_spec->bodies[0];
                DecodeByteFields(instruction_spec_body->byte_1, 0, decoding_context, instruction_input);
                DecodeByteFields(instruction_spec_body->byte_2, 1, decoding_context, instruction_input);
                DecodeByteFields(instruction_spec_body->byte_3456, 2, decoding_context, instruction_input);
            } break;
            case InstructionSpecType::ExtendedOpcode:
            {
                DecodeByteFields(OPCODE_EXT_BYTE_FIELDS, 1, decoding_context, instruction_input);

                instruction_spec_body = &instruction_spec->bodies[decoding_context->opcode_extension];
                DecodeByteFields(instruction_spec_body->byte_1, 0, decoding_context, instruction_input);
                DecodeByteFields(instruction_spec_body->byte_3456, 2, decoding_context, instruction_input);
            } break;
        }

        DecodeOperands(&instruction,
                       instruction_spec_body->format.operand_types,
                       ARRAY_SIZE(instruction_spec_body->format.operand_types),
                       decoding_context);
        instruction.mnemonic = instruction_spec_body->format.mnemonic;

        return instruction;
    }

    Instruction DecodeInstruction(InstructionDecodeContext *decoding_context,
                                  InstructionInput *instruction_input)
    {
        InstructionSpec instruction_spec = INSTRUCTION_SPECS[decoding_context->bytes[0]];

        return DecodeInstruction(&instruction_spec, decoding_context, instruction_input);
    }
}
