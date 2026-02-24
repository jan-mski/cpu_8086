typedef uint8_t (*displacement_decoder_t)(DecodingContext *decoding_context);

void DecodeW(uint8_t w_shift, DecodingContext *decoding_context)
{
    decoding_context->w = (decoding_context->bytes[0] >> w_shift) & 0b1;
}

void DecodeD(uint8_t d_shift, DecodingContext *decoding_context)
{
    decoding_context->d = (decoding_context->bytes[0] >> d_shift) & 0b1;
}

void DecodeS(uint8_t s_shift, DecodingContext *decoding_context)
{
    decoding_context->s = (decoding_context->bytes[0] >> s_shift) & 0b1;
}

void DecodeModAndRM(InstructionInput *instruction_input,
                    uint8_t mod_shift,
                    uint8_t r_m_shift,
                    DecodingContext *decoding_context)
{
    ReadNextBytesToIndex(instruction_input, decoding_context, 1);
    decoding_context->mod = (decoding_context->bytes[1] >> mod_shift) & 0b11;
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

void DecodeData(InstructionInput *instruction_input,
                uint8_t data_byte_1_index,
                DecodingContext *decoding_context)
{
    if (decoding_context->w == 0 || decoding_context->s == 1)
    {
        ReadNextBytesToIndex(instruction_input, decoding_context, data_byte_1_index);
        decoding_context->data = decoding_context->bytes[data_byte_1_index];
    } else if (decoding_context->s == 0)
    {
        uint8_t data_byte_2_index = data_byte_1_index + 1;
        ReadNextBytesToIndex(instruction_input, decoding_context, data_byte_2_index);
        decoding_context->data = (decoding_context->bytes[data_byte_2_index] << 8) | decoding_context->bytes[data_byte_1_index];
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
