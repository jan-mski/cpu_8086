#include "../decoder.h"

typedef uint8_t (*displacement_decoder_t)(OpDecodeData *decode_data);

void ReadNextBytesToIndex(const uint8_t byte_index, OpDecodeData *decode_data)
{
    while (decode_data->num_bytes_read <= byte_index)
    {
        ReadNextByte(decode_data);
    }
}

// # Single fields

void DecodeW(const uint8_t w_shift, OpDecodeData *decode_data)
{
    decode_data->w = (decode_data->bytes[0] >> w_shift) & 0b1;
}

void DecodeD(const uint8_t d_shift, OpDecodeData *decode_data)
{
    decode_data->d = (decode_data->bytes[0] >> d_shift) & 0b1;
}

void DecodeS(const uint8_t s_shift, OpDecodeData *decode_data)
{
    decode_data->s = (decode_data->bytes[0] >> s_shift) & 0b1;
}

void DecodeModRM(const uint8_t mod_shift, const uint8_t r_m_shift, OpDecodeData *decode_data)
{
    ReadNextBytesToIndex(1, decode_data);
    decode_data->mod = (decode_data->bytes[1] >> mod_shift) & 0b11;
    decode_data->r_m = (decode_data->bytes[1] >> r_m_shift) & 0b111;
}

void DecodeReg(const uint8_t reg_byte_index, const uint8_t reg_shift, OpDecodeData *decode_data)
{
    ReadNextBytesToIndex(reg_byte_index, decode_data);
    decode_data->reg = (decode_data->bytes[reg_byte_index] >> reg_shift) & 0b111;
}

void DecodeData(const uint8_t data_byte_1_index, OpDecodeData *decode_data)
{
    if (decode_data->w == 0 || decode_data->s == 1)
    {
        ReadNextBytesToIndex(data_byte_1_index, decode_data);
        decode_data->data = decode_data->bytes[data_byte_1_index];
    } else if (decode_data->s == 0)
    {
        const uint8_t data_byte_2_index = data_byte_1_index + 1;
        ReadNextBytesToIndex(data_byte_2_index, decode_data);
        decode_data->data = (decode_data->bytes[data_byte_2_index] << 8) | decode_data->bytes[data_byte_1_index];
    }
}

void DecodeAddr(OpDecodeData *decode_data)
{
    if (decode_data->w == 0)
    {
        ReadNextBytesToIndex(1, decode_data);
        decode_data->addr = decode_data->bytes[1];
    }
    else
    {
        ReadNextBytesToIndex(2, decode_data);
        decode_data->addr = (decode_data->bytes[2] << 8) | decode_data->bytes[1];
    }
}

void DecodeArithmeticMnemonic(OpDecodeData *decode_data)
{
    ReadNextBytesToIndex(1, decode_data);
    decode_data->common_mnemonic = (decode_data->bytes[1] >> 3) & 0b111;
}

// ## Displacement

uint8_t DecodeDisplacementNone(OpDecodeData *)
{
    return 0;
}

uint8_t DecodeDisplacement8Bit(OpDecodeData *decode_data)
{
    ReadNextBytesToIndex(2, decode_data);
    const uint8_t sign = (decode_data->bytes[2] >> 7) & 0b1;
    if (sign == 1)  // negative number, so we do two's complement
    {
        decode_data->displacement = -((decode_data->bytes[2] ^ 0b11111111) + 0b1);
    }
    else
    {
        decode_data->displacement = decode_data->bytes[2];
    }

    return 1;
}

uint8_t DecodeDisplacement16Bit(OpDecodeData *decode_data)
{
    ReadNextBytesToIndex(3, decode_data);
    decode_data->displacement = (decode_data->bytes[3] << 8) | decode_data->bytes[2];

    return 2;
}

uint8_t DecodeDisplacement(OpDecodeData *decode_data)
{
    switch (decode_data->mod)
    {
        case 0b00:
        {
            if (decode_data->r_m == 0b110)
            {
                return DecodeDisplacement16Bit(decode_data);
            }
            return DecodeDisplacementNone(decode_data);
        } break;
        case 0b01:
        {
            return DecodeDisplacement8Bit(decode_data);
        } break;
        case 0b10:
        {
            return DecodeDisplacement16Bit(decode_data);
        } break;
        default:
        {
            return DecodeDisplacementNone(decode_data);
        } break;
    }
}


// # Field aggregates

void DecodeFieldsRegisterOrMemoryAndEither(OpDecodeData *decode_data)
{
    DecodeD(1, decode_data);
    DecodeW(0, decode_data);
    DecodeModRM(6, 0, decode_data);
    DecodeReg(1, 3, decode_data);
    DecodeDisplacement(decode_data);
}

void DecodeFieldsRegisterOrMemoryAndImmediate(OpDecodeData *decode_data)
{
    DecodeW(0, decode_data);
    DecodeModRM(6, 0, decode_data);
    const uint8_t num_bytes_read = DecodeDisplacement(decode_data);
    DecodeData(2 + num_bytes_read, decode_data);
}

void DecodeFieldsRegisterAndImmediate(OpDecodeData *decode_data)
{
    DecodeW(3, decode_data);
    DecodeReg(0, 0, decode_data);
    DecodeData(1, decode_data);
}

void DecodeFieldsMemoryAndAccumulator(OpDecodeData *decode_data)
{
    DecodeW(0, decode_data);
    DecodeAddr(decode_data);
}

void DecodeFieldsAccumulatorAndImmediate(OpDecodeData *decode_data)
{
    DecodeW(0, decode_data);
    DecodeData(1, decode_data);
}