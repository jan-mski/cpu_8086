#include "../decoder.h"
#include "subdecoders.h"

typedef void (*op_decoder_t)(OpDecodeData *decode_data);

void DecodeUnsupported(OpDecodeData *decode_data)
{
    decode_data->asm_str[0] = '\0';
}

void DecodeMovRegisterMemory(OpDecodeData *decode_data)
{
    DecodeD(1, decode_data);
    DecodeW(0, decode_data);
    DecodeModRM(6, 0, decode_data);
    DecodeReg(1, 3, decode_data);
    DecodeDisplacement(decode_data);

    char reg_str[TRANSLATED_REG_MAX_LEN];
    TranslateReg(reg_str, decode_data);

    char r_m_str[TRANSLATED_R_M_MAX_LEN];
    TranslateRM(r_m_str, decode_data);

    if (decode_data->d == 0)
    {
        snprintf(decode_data->asm_str, sizeof(decode_data->asm_str), "mov %s, %s", r_m_str, reg_str);
    }
    else
    {
        snprintf(decode_data->asm_str, sizeof(decode_data->asm_str), "mov %s, %s", reg_str, r_m_str);
    }
}

void DecodeMovMemoryToAccumulator(OpDecodeData *decode_data)
{
    DecodeW(0, decode_data);
    DecodeAddr(decode_data);

    snprintf(decode_data->asm_str, sizeof(decode_data->asm_str), "mov ax, [%u]", decode_data->addr);
}

void DecodeMovAccumulatorToMemory(OpDecodeData *decode_data)
{
    DecodeW(0, decode_data);
    DecodeAddr(decode_data);

    snprintf(decode_data->asm_str, sizeof(decode_data->asm_str), "mov [%u], ax", decode_data->addr);}

void DecodeMovImmediateToRegister(OpDecodeData *decode_data)
{
    DecodeW(3, decode_data);
    DecodeReg(0, 0, decode_data);
    DecodeData(1, decode_data);

    char reg_str[TRANSLATED_REG_MAX_LEN];
    TranslateReg(reg_str, decode_data);

    snprintf(decode_data->asm_str, sizeof(decode_data->asm_str), "mov %s, %u", reg_str, decode_data->data);
}

void DecodeMovImmediateToRegisterOrMemory(OpDecodeData *decode_data)
{
    DecodeW(0, decode_data);
    DecodeModRM(6, 0, decode_data);
    const uint8_t num_bytes_read = DecodeDisplacement(decode_data);
    DecodeData(2 + num_bytes_read, decode_data);

    char r_m_str[TRANSLATED_R_M_MAX_LEN];
    TranslateRM(r_m_str, decode_data);

    if (decode_data->w == 0)
    {
        snprintf(decode_data->asm_str, sizeof(decode_data->asm_str), "mov %s, byte %u", r_m_str, decode_data->data);
    }
    else
    {
        snprintf(decode_data->asm_str, sizeof(decode_data->asm_str), "mov %s, word %u", r_m_str, decode_data->data);
    }
}

op_decoder_t OP_DECODERS[256] = {
    REPEAT_136(DecodeUnsupported),                   // 0b00000000 - 0b10000111 [  0 - 135]
    REPEAT_4(DecodeMovRegisterMemory),               // 0b10001000 - 0b10001011 [136 - 139]
    REPEAT_20(DecodeUnsupported),                    // 0b10001100 - 0b10011111 [140 - 159]
    REPEAT_2(DecodeMovMemoryToAccumulator),          // 0b10100000 - 0b10100001 [160 - 161]
    REPEAT_2(DecodeMovAccumulatorToMemory),          // 0b10100010 - 0b10100011 [162 - 163]
    REPEAT_12(DecodeUnsupported),                    // 0b10100100 - 0b10101111 [164 - 175]
    REPEAT_16(DecodeMovImmediateToRegister),         // 0b10110000 - 0b10111111 [176 - 191]
    REPEAT_6(DecodeUnsupported),                     // 0b11000000 - 0b11000101 [192 - 197]
    REPEAT_2(DecodeMovImmediateToRegisterOrMemory),  // 0b11000110 - 0b11000111 [198 - 199]
    REPEAT_56(DecodeUnsupported)                     // 0b11001000 - 0b11111111 [200 - 255]
};

void DecodeOp(OpDecodeData *decode_data)
{
    const op_decoder_t op_decoder = OP_DECODERS[decode_data->bytes[0]];
    op_decoder(decode_data);
}
