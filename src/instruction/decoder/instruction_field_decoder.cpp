typedef uint8_t (*displacement_decoder_t)(DecodingContext *decoding_context);

void DecodeD(FieldSpec field_spec, DecodingContext *decoding_context)
{
    decoding_context->d = field_spec.is_forced
                              ? field_spec.forced_value
                              : (decoding_context->bytes[0] >> field_spec.bit_shift) & 0b1;
}

void DecodeS(FieldSpec field_spec, DecodingContext *decoding_context)
{
    decoding_context->s = (decoding_context->bytes[0] >> field_spec.bit_shift) & 0b1;
}

void DecodeV(FieldSpec field_spec, DecodingContext *decoding_context)
{
    decoding_context->v = (decoding_context->bytes[0] >> field_spec.bit_shift) & 0b1;
}

void DecodeW(FieldSpec field_spec, DecodingContext *decoding_context)
{
    decoding_context->w = field_spec.is_forced
                              ? field_spec.forced_value
                              : (decoding_context->bytes[0] >> field_spec.bit_shift) & 0b1;
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

void DecodeDataLowByte(InstructionInput *instruction_input, DecodingContext *decoding_context) {
    uint8_t data_byte_1_index = decoding_context->num_bytes_read;
    ReadNextBytesToIndex(instruction_input, decoding_context, data_byte_1_index);
    decoding_context->data = decoding_context->bytes[data_byte_1_index];
}

void DecodeDataHighByte(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    if (decoding_context->w == 1 && decoding_context->s == 0)
    {
        uint8_t data_byte_2_index = decoding_context->num_bytes_read;
        ReadNextBytesToIndex(instruction_input, decoding_context, data_byte_2_index);
        decoding_context->data = (decoding_context->bytes[data_byte_2_index] << 8) | decoding_context->data;
    }
}

void DecodeAddrLowByte(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    uint8_t addr_byte_1_index = decoding_context->num_bytes_read;
    ReadNextBytesToIndex(instruction_input, decoding_context, addr_byte_1_index);
    decoding_context->addr = decoding_context->bytes[addr_byte_1_index];
}

void DecodeAddrHighByte(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    if (decoding_context->w == 1)
    {
        uint8_t addr_byte_2_index = decoding_context->num_bytes_read;
        ReadNextBytesToIndex(instruction_input, decoding_context, addr_byte_2_index);
        decoding_context->addr = (decoding_context->bytes[addr_byte_2_index] << 8) | decoding_context->addr;
    }
}

void DecodeOpcodeExtension(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    decoding_context->opcode_extension = (decoding_context->bytes[1] >> 3) & 0b111;
}

void DecodeDisplacementNone(DecodingContext *)
{

}

void DecodeDisplacement8Bit(InstructionInput *instruction_input,
                            DecodingContext *decoding_context)
{
    uint8_t displacement_byte_1_index = decoding_context->num_bytes_read;
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
}

void DecodeDisplacement16Bit(InstructionInput *instruction_input,
                             DecodingContext *decoding_context)
{
    uint8_t displacement_byte_1_index = decoding_context->num_bytes_read;
    uint8_t displacement_byte_2_index = displacement_byte_1_index + 1;
    ReadNextBytesToIndex(instruction_input, decoding_context, displacement_byte_2_index);
    decoding_context->displacement = (decoding_context->bytes[displacement_byte_2_index] << 8) |
        decoding_context->bytes[displacement_byte_1_index];
}

void DecodeDisplacement(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    switch (decoding_context->mod)
    {
        case 0b00:
        {
            if (decoding_context->r_m == 0b110)
            {
                DecodeDisplacement16Bit(instruction_input, decoding_context);
            }
            DecodeDisplacementNone(decoding_context);
        } break;
        case 0b01:
        {
            DecodeDisplacement8Bit(instruction_input, decoding_context);
        } break;
        case 0b10:
        {
            DecodeDisplacement16Bit(instruction_input, decoding_context);
        } break;
        default:
        {
            DecodeDisplacementNone(decoding_context);
        } break;
    }
}
