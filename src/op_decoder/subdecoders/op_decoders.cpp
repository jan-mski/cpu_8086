#include "../decoder.h"
#include "subdecoders.h"

typedef void (*op_decoder_t)(OpDecodeData *decode_data);

void DecodeUnsupported(OpDecodeData *)
{
}

// # MOV

void DecodeMOVRegisterOrMemoryToEither(OpDecodeData *decode_data)
{
    DecodeFieldsRegisterOrMemoryAndEither(decode_data);
    DecodeOperandsRegisterOrMemoryAndEither(decode_data);
    decode_data->mnemonic = "mov";
}

void DecodeMOVMemoryToAccumulator(OpDecodeData *decode_data)
{
    DecodeFieldsMemoryAndAccumulator(decode_data);
    DecodeOperandsAccumulatorAndMemory(decode_data);
    decode_data->mnemonic = "mov";
}

void DecodeMOVAccumulatorToMemory(OpDecodeData *decode_data)
{
    DecodeFieldsMemoryAndAccumulator(decode_data);
    DecodeOperandsMemoryAndAccumulator(decode_data);
    decode_data->mnemonic = "mov";
}

void DecodeMOVImmediateToRegister(OpDecodeData *decode_data)
{
    DecodeFieldsRegisterAndImmediate(decode_data);
    DecodeOperandsRegisterAndImmediate(decode_data);
    decode_data->mnemonic = "mov";
}

void DecodeMOVImmediateToRegisterOrMemory(OpDecodeData *decode_data)
{
    DecodeFieldsRegisterOrMemoryAndImmediate(decode_data);
    DecodeOperandsRegisterOrMemoryAndImmediate(decode_data);
    decode_data->mnemonic = "mov";
}

// # Arithmetic
const char *SIGNED_ARITHMETIC_MNEMONICS[] = {"add", 0, "adc", "sbb", 0, "sub", 0, "cmp"};

void DecodeSignedArithmeticImmediateAndRegisterOrMemory(OpDecodeData *decode_data)
{
    DecodeS(1, decode_data);
    DecodeArithmeticMnemonic(decode_data);
    DecodeFieldsRegisterOrMemoryAndImmediate(decode_data);
    DecodeOperandsRegisterOrMemoryAndImmediate(decode_data);
    decode_data->mnemonic = SIGNED_ARITHMETIC_MNEMONICS[decode_data->common_mnemonic];
}

// ## ADD

void DecodeADDRegisterOrMemoryToEither(OpDecodeData *decode_data)
{
    DecodeFieldsRegisterOrMemoryAndEither(decode_data);
    DecodeOperandsRegisterOrMemoryAndEither(decode_data);
    decode_data->mnemonic = "add";
}

void DecodeADDImmediateToAccumulator(OpDecodeData *decode_data)
{
    DecodeFieldsAccumulatorAndImmediate(decode_data);
    DecodeOperandsAccumulatorAndImmediate(decode_data);
    decode_data->mnemonic = "add";
}

// ## SUB

void DecodeSUBRegisterOrMemoryFromEither(OpDecodeData *decode_data)
{
    DecodeFieldsRegisterOrMemoryAndEither(decode_data);
    DecodeOperandsRegisterOrMemoryAndEither(decode_data);
    decode_data->mnemonic = "sub";
}

void DecodeSUBImmediateFromAccumulator(OpDecodeData *decode_data)
{
    DecodeFieldsAccumulatorAndImmediate(decode_data);
    DecodeOperandsAccumulatorAndImmediate(decode_data);
    decode_data->mnemonic = "sub";
}

// ## CMP

void DecodeCMPRegisterOrMemoryWithEither(OpDecodeData *decode_data)
{
    DecodeFieldsRegisterOrMemoryAndEither(decode_data);
    DecodeOperandsRegisterOrMemoryAndEither(decode_data);
    decode_data->mnemonic = "cmp";
}

void DecodeCMPImmediateWithAccumulator(OpDecodeData *decode_data)
{
    DecodeFieldsAccumulatorAndImmediate(decode_data);
    DecodeOperandsAccumulatorAndImmediate(decode_data);
    decode_data->mnemonic = "cmp";
}


op_decoder_t OP_DECODERS[256] = {
    REPEAT_4(DecodeADDRegisterOrMemoryToEither),                   // 00000000 - 00000011 [  0 -   3]
    REPEAT_2(DecodeADDImmediateToAccumulator),                     // 00000100 - 00000101 [  4 -   5]
    REPEAT_34(DecodeUnsupported),                                  // 00000110 - 00100111 [  6 -  39]
    REPEAT_4(DecodeSUBRegisterOrMemoryFromEither),                 // 00101000 - 00101011 [ 40 -  43]
    REPEAT_2(DecodeSUBImmediateFromAccumulator),                   // 00101100 - 00101101 [ 44 -  45]
    REPEAT_10(DecodeUnsupported),                                  // 00101110 - 00110111 [ 46 -  55]
    REPEAT_4(DecodeCMPRegisterOrMemoryWithEither),                 // 00111000 - 00111011 [ 56 -  59]
    REPEAT_2(DecodeCMPImmediateWithAccumulator),                   // 00111100 - 00111101 [ 60 -  61]
    REPEAT_66(DecodeUnsupported),                                  // 00111110 - 01111111 [ 62 - 127]
    REPEAT_4(DecodeSignedArithmeticImmediateAndRegisterOrMemory),  // 10000000 - 10000011 [128 - 131]
    REPEAT_4(DecodeUnsupported),                                   // 10000100 - 10000111 [132 - 135]
    REPEAT_4(DecodeMOVRegisterOrMemoryToEither),                   // 10001000 - 10001011 [136 - 139]
    REPEAT_20(DecodeUnsupported),                                  // 10001100 - 10011111 [140 - 159]
    REPEAT_2(DecodeMOVMemoryToAccumulator),                        // 10100000 - 10100001 [160 - 161]
    REPEAT_2(DecodeMOVAccumulatorToMemory),                        // 10100010 - 10100011 [162 - 163]
    REPEAT_12(DecodeUnsupported),                                  // 10100100 - 10101111 [164 - 175]
    REPEAT_16(DecodeMOVImmediateToRegister),                       // 10110000 - 10111111 [176 - 191]
    REPEAT_6(DecodeUnsupported),                                   // 11000000 - 11000101 [192 - 197]
    REPEAT_2(DecodeMOVImmediateToRegisterOrMemory),                // 11000110 - 11000111 [198 - 199]
    REPEAT_56(DecodeUnsupported)                                   // 11001000 - 11111111 [200 - 255]
};

void DecodeOp(OpDecodeData *decode_data)
{
    const op_decoder_t op_decoder = OP_DECODERS[decode_data->bytes[0]];
    op_decoder(decode_data);
}
