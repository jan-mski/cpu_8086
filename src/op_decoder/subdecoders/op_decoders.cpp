#include "../decoder.h"
#include "subdecoders.h"

typedef void (*op_decoder_t)(OpDecodeData *decode_data);
const char *mnemonic_mov = "mov";
const char *mnemonic_add = "add";

void DecodeUnsupported(OpDecodeData *)
{

}

void DecodeMovRegisterOrMemory(OpDecodeData *decode_data)
{
    decode_data->mnemonic = mnemonic_mov;
    DecodeFieldsRegisterOrMemoryAndEither(decode_data);
    DecodeOperandsRegisterOrMemoryAndEither(decode_data);
}

void DecodeMovMemoryToAccumulator(OpDecodeData *decode_data)
{
    decode_data->mnemonic = mnemonic_mov;
    DecodeFieldsMemoryAndAccumulator(decode_data);
    DecodeOperandsAccumulatorAndMemory(decode_data);
}

void DecodeMovAccumulatorToMemory(OpDecodeData *decode_data)
{
    decode_data->mnemonic = mnemonic_mov;
    DecodeFieldsMemoryAndAccumulator(decode_data);
    DecodeOperandsMemoryAndAccumulator(decode_data);
}

void DecodeMovImmediateToRegister(OpDecodeData *decode_data)
{
    decode_data->mnemonic = mnemonic_mov;
    DecodeFieldsRegisterAndImmediate(decode_data);
    DecodeOperandsRegisterAndImmediate(decode_data);
}

void DecodeMovImmediateToRegisterOrMemory(OpDecodeData *decode_data)
{
    decode_data->mnemonic = mnemonic_mov;
    DecodeFieldsRegisterOrMemoryAndImmediate(decode_data);
    DecodeOperandsRegisterOrMemoryAndImmediate(decode_data);
}

void DecodeAddRegisterOrMemory(OpDecodeData *decode_data)
{
    decode_data->mnemonic = mnemonic_add;
    DecodeFieldsRegisterOrMemoryAndEither(decode_data);
    DecodeOperandsRegisterOrMemoryAndEither(decode_data);
}

void DecodeAddImmediateToRegisterOrMemory(OpDecodeData *decode_data)
{
    decode_data->mnemonic = mnemonic_add;
    DecodeS(1, decode_data);
    DecodeFieldsRegisterOrMemoryAndImmediate(decode_data);
    DecodeOperandsRegisterOrMemoryAndImmediate(decode_data);
}

void DecodeAddImmediateToAccumulator(OpDecodeData *decode_data)
{
    decode_data->mnemonic = mnemonic_add;
    DecodeFieldsAccumulatorAndImmediate(decode_data);
    DecodeOperandsAccumulatorAndImmediate(decode_data);
}

op_decoder_t OP_DECODERS[256] = {
    REPEAT_4(DecodeAddRegisterOrMemory),             // 0b00000000 - 0b00000011 [  0 -   3]
    REPEAT_2(DecodeAddImmediateToAccumulator),       // 0b00000100 - 0b00000101 [  4 -   5]
    REPEAT_122(DecodeUnsupported),                   // 0b00000110 - 0b01111111 [  6 - 127]
    REPEAT_4(DecodeAddImmediateToRegisterOrMemory),  // 0b10000000 - 0b10000011 [128 - 131]
    REPEAT_4(DecodeUnsupported),                     // 0b10000100 - 0b10000111 [132 - 135]
    REPEAT_4(DecodeMovRegisterOrMemory),             // 0b10001000 - 0b10001011 [136 - 139]
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
