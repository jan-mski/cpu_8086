namespace cpu::instruction_decoding::fields
{
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::core::Register16BitId;
    using cpu::instruction_decoding::specs::FieldSpec;
    using cpu::instruction_decoding::specs::FieldSpecType;
    using cpu::instruction_decoding::specs::BYTE_FIELDS_MAX_LEN;
    using cpu::instruction_decoding::context::DecodingContext;
    using cpu::instruction_decoding::context::ReadNextInstructionByte;
    using cpu::instruction_decoding::context::ReadNextInstructionBytesUpToIdx;

    uint8_t DecodeField(FieldSpec field_spec,
                        uint8_t byte_idx,
                        DecodingContext *decoding_context,
                        CpuState *cpu_state,
                        Memory *memory)
    {
        ReadNextInstructionBytesUpToIdx(
            decoding_context,
            byte_idx,
            cpu_state->GetRegisterValue(Register16BitId::IP),
            memory);

        return field_spec.is_forced
                   ? field_spec.forced_value
                   : (decoding_context->bytes[byte_idx] >> field_spec.bit_shift) & field_spec.bit_mask;
    }

    uint8_t DecodeByte(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        ReadNextInstructionByte(decoding_context, cpu_state->GetRegisterValue(Register16BitId::IP), memory);

        return decoding_context->bytes[decoding_context->num_bytes_read - 1];
    }

    uint16_t DecodeHighByte(uint8_t low_byte_value,
                            DecodingContext *decoding_context,
                            CpuState *cpu_state,
                            Memory *memory)
    {
        return DecodeByte(decoding_context, cpu_state, memory) << 8 | low_byte_value;
    }

    uint16_t DecodeDataHighByte(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        return (decoding_context->w == 1 && decoding_context->s == 0)
                   ? DecodeHighByte(decoding_context->data, decoding_context, cpu_state, memory)
                   : decoding_context->data;
    }

    uint16_t DecodeDisplacement16Bit(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        uint8_t low_byte_value = DecodeByte(decoding_context, cpu_state, memory);

        return DecodeHighByte(low_byte_value, decoding_context, cpu_state, memory);
    }

    int32_t DecodeDisplacementBytes(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        int32_t displacement = 0;

        switch (decoding_context->mod)
        {
            case 0b00:
            {
                if (decoding_context->r_m == 0b110)
                {
                    displacement = DecodeDisplacement16Bit(decoding_context, cpu_state, memory);
                }
            } break;
            case 0b01:
            {
                displacement = (int8_t) DecodeByte(decoding_context, cpu_state, memory);
            } break;
            case 0b10:
            {
                displacement = DecodeDisplacement16Bit(decoding_context, cpu_state, memory);
            } break;
            default:
            {
            } break;
        }

        return displacement;
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
                    decoding_context->is_w_forced = field_spec.is_forced;
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
                case FieldSpecType::IP_INC_8:
                {
                    decoding_context->ip_increment = (int8_t) DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::IP_INC_LO:
                {
                    decoding_context->ip_increment = DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case FieldSpecType::IP_INC_HI:
                {
                    decoding_context->ip_increment = DecodeHighByte(
                        decoding_context->ip_increment,
                        decoding_context,
                        cpu_state,
                        memory);
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
                    decoding_context->addr = DecodeHighByte(
                        decoding_context->addr,
                        decoding_context,
                        cpu_state,
                        memory);
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
