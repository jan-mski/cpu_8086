#include "../decoder.h"

typedef uint8_t (*displacement_decoder_t)(OpDecodeData *decode_data);

void ReadNextBytesToIndex(const uint8_t byte_index, OpDecodeData *decode_data)
{
    while (decode_data->num_bytes_read <= byte_index)
    {
        ReadNextByte(decode_data);
    }
}

void DecodeW(const uint8_t w_shift, OpDecodeData *decode_data)
{
    decode_data->w = (decode_data->bytes[0] >> w_shift) & 0b1;
}

void DecodeD(const uint8_t d_shift, OpDecodeData *decode_data)
{
    decode_data->d = (decode_data->bytes[0] >> d_shift) & 0b1;
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
    ReadNextBytesToIndex(data_byte_1_index, decode_data);
    if (decode_data->w == 0)
    {
        decode_data->data = decode_data->bytes[data_byte_1_index];
    } else
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

// index: (mod << 3 | r_m), where mod is 2-bit long, r_m is 3-bit long, which makes a 5-bit long index
displacement_decoder_t DISPLACEMENT_DECODERS[32] = {
    REPEAT_6(DecodeDisplacementNone),   // 0b00000 - 0b00101
    DecodeDisplacement16Bit,            // 0b00110
    DecodeDisplacementNone,             // 0b00111
    REPEAT_8(DecodeDisplacement8Bit),   // 0b01000 - 0b01111
    REPEAT_8(DecodeDisplacement16Bit),  // 0b10000 - 0b10111
    REPEAT_8(DecodeDisplacementNone)    // 0b11000 - 0b11111
};

uint8_t DecodeDisplacement(OpDecodeData *decode_data)
{
    const uint8_t index = (decode_data->mod << 3) | decode_data->r_m;
    const displacement_decoder_t displacement_decoder = DISPLACEMENT_DECODERS[index];

    return displacement_decoder(decode_data);
}
