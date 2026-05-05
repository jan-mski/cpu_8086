namespace instruction_decoding::fields
{
    namespace mem = ::memory;
    namespace cpu = ::cpu;
    namespace dec_ctx = ::instruction_decoding::context;
    namespace dec_spx = ::instruction_decoding::specs;

    U8 DecodeField(dec_spx::FieldSpec field_spec,
                   U8 byte_idx,
                   dec_ctx::DecodingContext* decoding_context,
                   cpu::CpuState* cpu_state,
                   mem::Memory* memory)
    {
        dec_ctx::ReadNextInstructionBytesUpToIdx(
            decoding_context,
            byte_idx,
            cpu::GetRegisterValue(cpu_state, cpu::Register16BitId_IP),
            memory);

        return field_spec.is_forced
                   ? field_spec.forced_value
                   : (decoding_context->bytes[byte_idx] >> field_spec.bit_shift) & field_spec.bit_mask;
    }

    U8 DecodeByte(dec_ctx::DecodingContext* decoding_context,
                  cpu::CpuState* cpu_state,
                  mem::Memory* memory)
    {
        dec_ctx::ReadNextInstructionByte(
            decoding_context,
            cpu::GetRegisterValue(cpu_state, cpu::Register16BitId_IP),
            memory);

        return decoding_context->bytes[decoding_context->num_bytes_read - 1];
    }

    U16 DecodeHighByte(U8 low_byte_value,
                       dec_ctx::DecodingContext* decoding_context,
                       cpu::CpuState* cpu_state,
                       mem::Memory* memory)
    {
        return DecodeByte(decoding_context, cpu_state, memory) << 8 | low_byte_value;
    }

    U16 DecodeDataHighByte(dec_ctx::DecodingContext* decoding_context,
                           cpu::CpuState* cpu_state,
                           mem::Memory* memory)
    {
        return (decoding_context->w == 1 && decoding_context->s == 0)
                   ? DecodeHighByte(decoding_context->data, decoding_context, cpu_state, memory)
                   : decoding_context->data;
    }

    U16 DecodeDisplacement16Bit(dec_ctx::DecodingContext* decoding_context,
                                cpu::CpuState* cpu_state,
                                mem::Memory* memory)
    {
        U8 low_byte_value = DecodeByte(decoding_context, cpu_state, memory);

        return DecodeHighByte(low_byte_value, decoding_context, cpu_state, memory);
    }

    I32 DecodeDisplacementBytes(dec_ctx::DecodingContext* decoding_context,
                                cpu::CpuState* cpu_state,
                                mem::Memory* memory)
    {
        I32 displacement = 0;

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
                displacement = (I8) DecodeByte(decoding_context, cpu_state, memory);
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

    void DecodeByteFields(dec_spx::FieldSpec* byte_field_specs,
                          U8 byte_idx,
                          dec_ctx::DecodingContext* decoding_context,
                          cpu::CpuState* cpu_state,
                          mem::Memory* memory)
    {
        for (U8 i = 0; i < dec_spx::BYTE_FIELDS_MAX_LEN; ++i)
        {
            dec_spx::FieldSpec field_spec = byte_field_specs[i];

            if (field_spec.type == dec_spx::FieldSpecType_None)
            {
                break;
            }

            switch (field_spec.type)
            {
                case dec_spx::FieldSpecType_None:
                {
                } break;
                case dec_spx::FieldSpecType_D:
                {
                    decoding_context->d = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_S:
                {
                    decoding_context->s = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_V:
                {
                    decoding_context->v = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_W:
                {
                    decoding_context->w = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                    decoding_context->is_w_forced = field_spec.is_forced;
                } break;
                case dec_spx::FieldSpecType_MOD:
                {
                    decoding_context->mod = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_RM:
                {
                    decoding_context->r_m = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_REG:
                {
                    decoding_context->reg = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_SR:
                {
                    decoding_context->sr = DecodeField(field_spec, byte_idx, decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_IP_INC_8:
                {
                    decoding_context->ip_increment = (I8) DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_IP_INC_LO:
                {
                    decoding_context->ip_increment = DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_IP_INC_HI:
                {
                    decoding_context->ip_increment = DecodeHighByte(
                        decoding_context->ip_increment,
                        decoding_context,
                        cpu_state,
                        memory);
                } break;
                case dec_spx::FieldSpecType_DISP_LO_HI:
                {
                    decoding_context->displacement = DecodeDisplacementBytes(decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_DATA_8:
                {
                    decoding_context->data = DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_DATA_LO:
                {
                    decoding_context->data = DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_DATA_HI:
                {
                    decoding_context->data = DecodeDataHighByte(decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_ADDR_LO:
                {
                    decoding_context->addr = DecodeByte(decoding_context, cpu_state, memory);
                } break;
                case dec_spx::FieldSpecType_ADDR_HI:
                {
                    decoding_context->addr = DecodeHighByte(
                        decoding_context->addr,
                        decoding_context,
                        cpu_state,
                        memory);
                } break;
                case dec_spx::FieldSpecType_OpcodeExtension:
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
