uint8_t DecodeField(FieldSpec field_spec,
                    uint8_t byte_idx,
                    InstructionInput *instruction_input,
                    DecodingContext *decoding_context)
{
    ReadBytesUpToIdx(instruction_input, decoding_context, byte_idx);

    return field_spec.is_forced
               ? field_spec.forced_value
               : (decoding_context->bytes[byte_idx] >> field_spec.bit_shift) & field_spec.bit_mask;
}

uint8_t DecodeByte(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    ReadNextByte(instruction_input, decoding_context);

    return decoding_context->bytes[decoding_context->num_bytes_read - 1];
}

int32_t DecodeHighByte(int32_t low_byte_value, InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    return DecodeByte(instruction_input, decoding_context) << 8 | low_byte_value;
}

int32_t DecodeDataHighByte(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    return (decoding_context->w == 1 && decoding_context->s == 0)
               ? DecodeHighByte(decoding_context->data, instruction_input, decoding_context)
               : decoding_context->data;
}

int32_t DecodeAddrHighByte(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    return decoding_context->w == 1
               ? DecodeHighByte(decoding_context->addr, instruction_input, decoding_context)
               : decoding_context->addr;
}

int32_t DecodeDisplacement8Bit(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    int32_t byte_value = DecodeByte(instruction_input, decoding_context);

    return (byte_value >> 7) & 0b1
               ? -((byte_value ^ 0b11111111) + 0b1)  // negative number, so we do two's complement
               : byte_value;
}

int32_t DecodeDisplacement16Bit(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    int32_t low_byte_value = DecodeByte(instruction_input, decoding_context);

    return DecodeHighByte(low_byte_value, instruction_input, decoding_context);
}

int32_t DecodeDisplacement(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    switch (decoding_context->mod)
    {
        case 0b00:
        {
            if (decoding_context->r_m == 0b110)
            {
                return DecodeDisplacement16Bit(instruction_input, decoding_context);
            }
        } break;
        case 0b01:
        {
            return DecodeDisplacement8Bit(instruction_input, decoding_context);
        } break;
        case 0b10:
        {
            return DecodeDisplacement16Bit(instruction_input, decoding_context);
        } break;
        default:
        {

        } break;
    }

    return 0;
}
