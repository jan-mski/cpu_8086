#include "../decoder.h"
#include "subdecoders.h"

typedef void (*op_decoder_t)(OpDecodeData *decode_data);

void DecodeUnsupported(OpDecodeData *decode_data)
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

// ## Return from CALL

void DecodeJO(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jo";
}

void DecodeJNO(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jno";
}

void DecodeJB_JNAE(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jb";
}

void DecodeJNB_JAE(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jnb";
}

void DecodeJE_JZ(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "je";
}

void DecodeJNE_JNZ(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jne";
}

void DecodeJBE_JNA(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jbe";
}

void DecodeJNBE_JA(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jnbe";
}

void DecodeJS(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "js";
}

void DecodeJNS(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jns";
}

void DecodeJP_JPE(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jp";
}

void DecodeJNP_JPO(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jnp";
}

void DecodeJL_JNGE(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jl";
}

void DecodeJNL_JGE(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jnl";
}

void DecodeJLE_JNG(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jle";
}

void DecodeJNLE_JG(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jnle";
}

void DecodeLOOPNZ_LOOPNE(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "loopnz";
}

void DecodeLOOPZ_LOOPE(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "loopz";
}

void DecodeLOOP(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "loop";
}

void DecodeJCXZ(OpDecodeData *decode_data)
{
    DecodeFieldsReturnFromCall(decode_data);
    DecodeOperandsReturnFromCall(decode_data);
    decode_data->mnemonic = "jcxz";
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
    REPEAT_50(DecodeUnsupported),                                  // 00111110 - 01101111 [ 62 - 111]
    DecodeJO,                                                      // 01110000 - 01110000 [112 - 112]
    DecodeJNO,                                                     // 01110001 - 01110001 [113 - 113]
    DecodeJB_JNAE,                                                 // 01110010 - 01110010 [114 - 114]
    DecodeJNB_JAE,                                                 // 01110011 - 01110011 [115 - 115]
    DecodeJE_JZ,                                                   // 01110100 - 01110100 [116 - 116]
    DecodeJNE_JNZ,                                                 // 01110101 - 01110101 [117 - 117]
    DecodeJBE_JNA,                                                 // 01110110 - 01110110 [118 - 118]
    DecodeJNBE_JA,                                                 // 01110111 - 01110111 [119 - 119]
    DecodeJS,                                                      // 01111000 - 01111000 [120 - 120]
    DecodeJNS,                                                     // 01111001 - 01111001 [121 - 121]
    DecodeJP_JPE,                                                  // 01111010 - 01111010 [122 - 122]
    DecodeJNP_JPO,                                                 // 01111011 - 01111011 [123 - 123]
    DecodeJL_JNGE,                                                 // 01111100 - 01111100 [124 - 124]
    DecodeJNL_JGE,                                                 // 01111101 - 01111101 [125 - 125]
    DecodeJLE_JNG,                                                 // 01111110 - 01111110 [126 - 126]
    DecodeJNLE_JG,                                                 // 01111111 - 01111111 [127 - 127]
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
    REPEAT_24(DecodeUnsupported),                                  // 11001000 - 11011111 [200 - 223]
    DecodeLOOPNZ_LOOPNE,                                           // 11100000 - 11100000 [224 - 224]
    DecodeLOOPZ_LOOPE,                                             // 11100001 - 11100001 [225 - 225]
    DecodeLOOP,                                                    // 11100010 - 11100010 [226 - 226]
    DecodeJCXZ,                                                    // 11100011 - 11100011 [227 - 227]
    REPEAT_28(DecodeUnsupported),                                  // 11100100 - 11111111 [228 - 255]
};

void DecodeOp(OpDecodeData *decode_data)
{
    const op_decoder_t op_decoder = OP_DECODERS[decode_data->bytes[0]];
    op_decoder(decode_data);
}
