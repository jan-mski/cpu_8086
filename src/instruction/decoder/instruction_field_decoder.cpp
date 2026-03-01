typedef uint8_t (*displacement_decoder_t)(DecodingContext *decoding_context);

void DecodeW(FieldSpec field_spec, DecodingContext *decoding_context)
{
    decoding_context->w = field_spec.is_forced
                           ? field_spec.forced_value
                           : (decoding_context->bytes[field_spec.byte_index] >> field_spec.bit_shift) & 0b1;
}

void DecodeD(FieldSpec field_spec, DecodingContext *decoding_context)
{
    decoding_context->d = field_spec.is_forced
                              ? field_spec.forced_value
                              : (decoding_context->bytes[field_spec.byte_index] >> field_spec.bit_shift) & 0b1;
}

void DecodeS(FieldSpec field_spec, DecodingContext *decoding_context)
{
    decoding_context->s = field_spec.is_forced
                             ? field_spec.forced_value
                             : (decoding_context->bytes[field_spec.byte_index] >> field_spec.bit_shift) & 0b1;
}

void DecodeMod(InstructionInput *instruction_input, uint8_t mod_shift, DecodingContext *decoding_context)
{
    ReadNextBytesToIndex(instruction_input, decoding_context, 1);
    decoding_context->mod = (decoding_context->bytes[1] >> mod_shift) & 0b11;
}

void DecodeRM(InstructionInput *instruction_input, uint8_t r_m_shift, DecodingContext *decoding_context)
{
    ReadNextBytesToIndex(instruction_input, decoding_context, 1);
    decoding_context->r_m = (decoding_context->bytes[1] >> r_m_shift) & 0b111;
}

void DecodeReg(InstructionInput *instruction_input,
               uint8_t reg_byte_index,
               uint8_t reg_shift,
               DecodingContext *decoding_context)
{
    ReadNextBytesToIndex(instruction_input, decoding_context, reg_byte_index);
    decoding_context->reg = (decoding_context->bytes[reg_byte_index] >> reg_shift) & 0b111;
}

void DecodeSR(InstructionInput *instruction_input,
               uint8_t sr_byte_index,
               uint8_t sr_shift,
               DecodingContext *decoding_context)
{
    ReadNextBytesToIndex(instruction_input, decoding_context, sr_byte_index);
    decoding_context->sr = (decoding_context->bytes[sr_byte_index] >> sr_shift) & 0b11;
}

void DecodeData8Bit(InstructionInput *instruction_input, DecodingContext *decoding_context) {
    uint8_t data_byte_1_index = decoding_context->num_bytes_read;
    ReadNextBytesToIndex(instruction_input, decoding_context, data_byte_1_index);
    decoding_context->data = decoding_context->bytes[data_byte_1_index];
}

void DecodeData16Bit(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    uint8_t data_byte_1_index = decoding_context->num_bytes_read;
    uint8_t data_byte_2_index = data_byte_1_index + 1;
    ReadNextBytesToIndex(instruction_input, decoding_context, data_byte_2_index);
    decoding_context->data = (decoding_context->bytes[data_byte_2_index] << 8) |
                             decoding_context->bytes[data_byte_1_index];
}

void DecodeData(InstructionInput *instruction_input,
                DecodingContext *decoding_context)
{
    if (decoding_context->w == 0 || decoding_context->s == 1)
    {
        DecodeData8Bit(instruction_input, decoding_context);
    } else if (decoding_context->s == 0)
    {
        DecodeData16Bit(instruction_input, decoding_context);
    }
}

void DecodeAddr(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    if (decoding_context->w == 0)
        {
        ReadNextBytesToIndex(instruction_input, decoding_context, 1);
        decoding_context->addr = decoding_context->bytes[1];
    }
    else
    {
        ReadNextBytesToIndex(instruction_input, decoding_context, 2);
        decoding_context->addr = (decoding_context->bytes[2] << 8) | decoding_context->bytes[1];
    }
}

void DecodeArithmeticMnemonic(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    ReadNextBytesToIndex(instruction_input, decoding_context, 1);
    decoding_context->common_mnemonic = (decoding_context->bytes[1] >> 3) & 0b111;
}

uint8_t DecodeDisplacementNone(DecodingContext *)
{
    return 0;
}

uint8_t DecodeDisplacement8Bit(InstructionInput *instruction_input,
                    uint8_t displacement_byte_1_index,
                    DecodingContext *decoding_context)
{
    ReadNextBytesToIndex(instruction_input, decoding_context, displacement_byte_1_index);
    uint8_t sign = (decoding_context->bytes[displacement_byte_1_index] >> 7) & 0b1;
    if (sign == 1)  // negative number, so we do two's complement
    {
        decoding_context->displacement = -((decoding_context->bytes[displacement_byte_1_index] ^ 0b11111111) + 0b1);
    }
    else
    {
        decoding_context->displacement = decoding_context->bytes[displacement_byte_1_index];
    }

    return 1;
}

uint8_t DecodeDisplacement16Bit(InstructionInput *instruction_input,
                                uint8_t displacement_byte_1_index,
                                DecodingContext *decoding_context)
{
    uint8_t displacement_byte_2_index = displacement_byte_1_index + 1;
    ReadNextBytesToIndex(instruction_input, decoding_context, displacement_byte_2_index);
    decoding_context->displacement = (decoding_context->bytes[displacement_byte_2_index] << 8) |
        decoding_context->bytes[displacement_byte_1_index];

    return 2;
}

uint8_t DecodeDisplacement(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    switch (decoding_context->mod)
    {
        case 0b00:
        {
            if (decoding_context->r_m == 0b110)
            {
                return DecodeDisplacement16Bit(instruction_input, 2, decoding_context);
            }
            return DecodeDisplacementNone(decoding_context);
        } break;
        case 0b01:
        {
            return DecodeDisplacement8Bit(instruction_input, 2, decoding_context);
        } break;
        case 0b10:
        {
            return DecodeDisplacement16Bit(instruction_input, 2, decoding_context);
        } break;
        default:
        {
            return DecodeDisplacementNone(decoding_context);
        } break;
    }
}
