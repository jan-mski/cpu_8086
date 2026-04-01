namespace cpu::instruction_decoding::context
{
    using memory::Memory;
    using memory::ReadByte;
    using cpu::core::CpuState;
    using cpu::core::RegisterId;

    size_t ReadNextInstructionByte(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        uint16_t instruction_pointer = cpu_state->GetRegisterValue(RegisterId::IP);

        size_t num_bytes_read = ReadByte(
            decoding_context->bytes + decoding_context->num_bytes_read,
            instruction_pointer + decoding_context->num_bytes_read,
            memory);
        decoding_context->num_bytes_read += num_bytes_read;

        return num_bytes_read;
    }

    void ReadNextInstructionBytesUpToIdx(DecodingContext *decoding_context,
                                         uint8_t byte_idx,
                                         CpuState *cpu_state,
                                         Memory *memory)
    {
        while (decoding_context->num_bytes_read <= byte_idx)
        {
            ReadNextInstructionByte(decoding_context, cpu_state, memory);
        }
    }
}

namespace cpu::instruction_decoding::fields
{
    using memory::Memory;
    using memory::ReadByte;
    using cpu::core::CpuState;
    using cpu::instruction_decoding::context::DecodingContext;
    using cpu::instruction_decoding::context::ReadNextInstructionByte;
    using cpu::instruction_decoding::context::ReadNextInstructionBytesUpToIdx;

    uint8_t DecodeField(FieldSpec field_spec,
                        uint8_t byte_idx,
                        DecodingContext *decoding_context,
                        CpuState *cpu_state,
                        Memory *memory)
    {
        ReadNextInstructionBytesUpToIdx(decoding_context, byte_idx, cpu_state, memory);

        return field_spec.is_forced
                   ? field_spec.forced_value
                   : (decoding_context->bytes[byte_idx] >> field_spec.bit_shift) & field_spec.bit_mask;
    }

    uint8_t DecodeByte(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        ReadNextInstructionByte(decoding_context, cpu_state, memory);

        return decoding_context->bytes[decoding_context->num_bytes_read - 1];
    }

    int32_t DecodeHighByte(int32_t low_byte_value,
                           DecodingContext *decoding_context,
                           CpuState *cpu_state,
                           Memory *memory)
    {
        return DecodeByte(decoding_context, cpu_state, memory) << 8 | low_byte_value;
    }

    int32_t DecodeDataHighByte(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        return (decoding_context->w == 1 && decoding_context->s == 0)
                   ? DecodeHighByte(decoding_context->data, decoding_context, cpu_state, memory)
                   : decoding_context->data;
    }

    int32_t DecodeAddrHighByte(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        return decoding_context->w == 1
                   ? DecodeHighByte(decoding_context->addr, decoding_context, cpu_state, memory)
                   : decoding_context->addr;
    }

    int32_t DecodeDisplacement8Bit(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        int32_t byte_value = DecodeByte(decoding_context, cpu_state, memory);

        return (byte_value >> 7) & 0b1
                   ? -((byte_value ^ 0b11111111) + 0b1) // negative number, so we do two's complement
                   : byte_value;
    }

    int32_t DecodeDisplacement16Bit(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        int32_t low_byte_value = DecodeByte(decoding_context, cpu_state, memory);

        return DecodeHighByte(low_byte_value, decoding_context, cpu_state, memory);
    }

    int32_t DecodeDisplacementBytes(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        switch (decoding_context->mod)
        {
            case 0b00:
            {
                if (decoding_context->r_m == 0b110)
                {
                    return DecodeDisplacement16Bit(decoding_context, cpu_state, memory);
                }
            } break;
            case 0b01:
            {
                return DecodeDisplacement8Bit(decoding_context, cpu_state, memory);
            } break;
            case 0b10:
            {
                return DecodeDisplacement16Bit(decoding_context, cpu_state, memory);
            } break;
            default:
            {
            } break;
        }

        return 0;
    }

    void DecodeByteFields(FieldSpec *byte_field_specs,
                          uint8_t byte_idx,
                          DecodingContext *decoding_context,
                          CpuState *cpu_state,
                          Memory *memory)
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
                    decoding_context->d = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::S:
                {
                    decoding_context->s = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::V:
                {
                    decoding_context->v = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::W:
                {
                    decoding_context->w = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::MOD:
                {
                    decoding_context->mod = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::RM:
                {
                    decoding_context->r_m = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::REG:
                {
                    decoding_context->reg = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::SR:
                {
                    decoding_context->sr = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::DISP_8:
                {
                    decoding_context->displacement = DecodeDisplacement8Bit(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::DISP_LO_HI:
                {
                    decoding_context->displacement = DecodeDisplacementBytes(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::DATA_8:
                {
                    decoding_context->data = DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::DATA_LO:
                {
                    decoding_context->data = DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::DATA_HI:
                {
                    decoding_context->data = DecodeDataHighByte(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::ADDR_LO:
                {
                    decoding_context->addr = DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::ADDR_HI:
                {
                    decoding_context->addr = DecodeAddrHighByte(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::OpcodeExtension:
                {
                    decoding_context->opcode_extension = DecodeField(
                        field_spec,
                        byte_idx,
                        decoding_context,
                        cpu_state,
                        memory);
                } break;
            }
        }
    }
}

namespace cpu::instruction_decoding::operands
{
    using cpu::core::RegisterId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Operand;
    using cpu::instruction::OperandType;
    using cpu::instruction::MemoryAddressQualifier;
    using cpu::instruction_decoding::context::DecodingContext;

    void SetDirectAddressFromDisplacement(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::MemoryAddress;
        operand->memory_address.direct = true;
        operand->memory_address.displacement = decoding_context->displacement;
    }

    void SetEffectiveAddress(Operand *operand, DecodingContext *decoding_context)
    {
        RegisterId effective_address_registers[][2] = {
            {RegisterId::BX, RegisterId::SI},
            {RegisterId::BX, RegisterId::DI},
            {RegisterId::BP, RegisterId::SI},
            {RegisterId::BP, RegisterId::DI},
            {RegisterId::SI},
            {RegisterId::DI},
            {RegisterId::BP},
            {RegisterId::BX}
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
                RegisterId::AL, RegisterId::CL, RegisterId::DL,
                RegisterId::BL, RegisterId::AH, RegisterId::CH,
                RegisterId::DH, RegisterId::BH
            },
            {
                RegisterId::AX, RegisterId::CX, RegisterId::DX,
                RegisterId::BX, RegisterId::SP, RegisterId::BP,
                RegisterId::SI, RegisterId::DI
            }
        };

        operand->type = OperandType::Register;
        operand->register_id = registers_by_w[w][reg_or_r_m];
    }

    void DecodeOperandRegisterOrMemoryAddress(Operand *operand, DecodingContext *decoding_context)
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

    void DecodeOperandRegister(Operand *operand, DecodingContext *decoding_context)
    {
        SetRegister(operand, decoding_context->w, decoding_context->reg);
    }

    void DecodeOperandSegmentRegister(Operand *operand, DecodingContext *decoding_context)
    {
        RegisterId segment_registers[] = {
            RegisterId::ES, RegisterId::CS, RegisterId::SS, RegisterId::DS
        };

        operand->type = OperandType::Register;
        operand->register_id = segment_registers[decoding_context->sr];
    }

    void DecodeOperandImmediate(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::Immediate;
        operand->immediate_value = decoding_context->data;
    }

    void DecodeOperandAccumulator(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::Register;
        operand->register_id = decoding_context->w == 1
                                   ? RegisterId::AX
                                   : RegisterId::AL;
    }

    void DecodeOperandDataRegister(Operand *operand, DecodingContext *_)
    {
        operand->type = OperandType::Register;
        operand->register_id = RegisterId::DX;
    }

    void DecodeOperandDirectAddress(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::MemoryAddress;
        operand->memory_address.direct = true;
        operand->memory_address.displacement = decoding_context->addr;
    }

    void DecodeOperandLabelLikeDisplacement(Operand *operand, DecodingContext *decoding_context)
    {
        operand->type = OperandType::LabelLikeDisplacement;
        operand->label_like_displacement = decoding_context->displacement;
    }

    void DecodeOperandShiftRotateCount(Operand *operand, DecodingContext *decoding_context)
    {
        if (decoding_context->v == 0)
        {
            operand->type = OperandType::Immediate;
            operand->immediate_value = 1;
        } else
        {
            operand->type = OperandType::Register;
            operand->register_id = RegisterId::CL;
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
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::instruction::Instruction;
    using cpu::instruction_decoding::context::DecodingContext;
    using cpu::instruction_decoding::fields::DecodeByteFields;
    using cpu::instruction_decoding::operands::DecodeOperands;
    using cpu::instruction_decoding::specs::InstructionSpec;
    using cpu::instruction_decoding::specs::InstructionSpecBody;
    using cpu::instruction_decoding::specs::InstructionSpecType;
    using cpu::instruction_decoding::specs::OPCODE_EXT_BYTE_FIELDS;
    using cpu::instruction_decoding::specs::INSTRUCTION_SPECS;

    Instruction DecodeInstruction(InstructionSpec *instruction_spec,
                                  DecodingContext *decoding_context,
                                  CpuState *cpu_state,
                                  Memory *memory)
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
                DecodeByteFields(instruction_spec_body->byte_1, 0, decoding_context, cpu_state, memory);
                DecodeByteFields(instruction_spec_body->byte_2, 1, decoding_context, cpu_state, memory);
                DecodeByteFields(instruction_spec_body->byte_3456, 2, decoding_context, cpu_state, memory);
            } break;
            case InstructionSpecType::ExtendedOpcode:
            {
                DecodeByteFields(OPCODE_EXT_BYTE_FIELDS, 1, decoding_context, cpu_state, memory);

                instruction_spec_body = &instruction_spec->bodies[decoding_context->opcode_extension];
                DecodeByteFields(instruction_spec_body->byte_1, 0, decoding_context, cpu_state, memory);
                DecodeByteFields(instruction_spec_body->byte_3456, 2, decoding_context, cpu_state, memory);
            } break;
        }

        DecodeOperands(&instruction,
                       instruction_spec_body->format.operand_types,
                       ARRAY_SIZE(instruction_spec_body->format.operand_types),
                       decoding_context);
        instruction.mnemonic = instruction_spec_body->format.mnemonic;

        return instruction;
    }

    Instruction DecodeInstruction(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        InstructionSpec instruction_spec = INSTRUCTION_SPECS[decoding_context->bytes[0]];

        return DecodeInstruction(&instruction_spec, decoding_context, cpu_state, memory);
    }
}
