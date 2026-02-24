typedef void (*inst_decoder_t)(InstructionInput *instruction_input, DecodingContext *decoding_context);

void DecodeUnsupported(InstructionInput *instruction_input, DecodingContext *decoding_context)
{

}

// # MOV

void DecodeMOVRegisterOrMemoryToEither(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeD(1, decoding_context);
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeReg(instruction_input, 1, 3, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    DecodeOperandsRegisterOrMemoryAndEither(decoding_context);
    decoding_context->mnemonic = MNEMONIC_MOV;
}

void DecodeMOVMemoryToAccumulator(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeAddr(instruction_input, decoding_context);

    DecodeOperandsAccumulatorAndMemory(decoding_context);
    decoding_context->mnemonic = MNEMONIC_MOV;
}

void DecodeMOVAccumulatorToMemory(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeAddr(instruction_input, decoding_context);

    DecodeOperandsMemoryAndAccumulator(decoding_context);
    decoding_context->mnemonic = MNEMONIC_MOV;
}

void DecodeMOVImmediateToRegister(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(3, decoding_context);
    DecodeReg(instruction_input, 0, 0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    DecodeOperandsRegisterAndImmediate(decoding_context);
    decoding_context->mnemonic = MNEMONIC_MOV;
}

void DecodeMOVImmediateToRegisterOrMemory(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    const uint8_t num_bytes_read = DecodeDisplacement(instruction_input, decoding_context);
    DecodeData(instruction_input, 2 + num_bytes_read, decoding_context);

    DecodeOperandsRegisterOrMemoryAndImmediate(decoding_context);
    decoding_context->mnemonic = MNEMONIC_MOV;
}

// # Arithmetic
Mnemonic SIGNED_ARITHMETIC_MNEMONICS[] = {
    MNEMONIC_ADD,
    MNEMONIC_NONE,
    MNEMONIC_NONE,  // "adc" - unsupported
    MNEMONIC_NONE,  // "sbb"
    MNEMONIC_NONE,
    MNEMONIC_SUB,
    MNEMONIC_NONE,
    MNEMONIC_CMP
};

void DecodeSignedArithmeticImmediateAndRegisterOrMemory(InstructionInput *instruction_input,
                                                        DecodingContext *decoding_context)
{
    DecodeS(1, decoding_context);
    DecodeArithmeticMnemonic(instruction_input, decoding_context);

    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    const uint8_t num_bytes_read = DecodeDisplacement(instruction_input, decoding_context);
    DecodeData(instruction_input, 2 + num_bytes_read, decoding_context);

    DecodeOperandsRegisterOrMemoryAndImmediate(decoding_context);
    decoding_context->mnemonic = SIGNED_ARITHMETIC_MNEMONICS[decoding_context->common_mnemonic];
}

// ## ADD

void DecodeADDRegisterOrMemoryToEither(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeD(1, decoding_context);
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeReg(instruction_input, 1, 3, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    DecodeOperandsRegisterOrMemoryAndEither(decoding_context);
    decoding_context->mnemonic = MNEMONIC_ADD;
}

void DecodeADDImmediateToAccumulator(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    DecodeOperandsAccumulatorAndImmediate(decoding_context);
    decoding_context->mnemonic = MNEMONIC_ADD;
}

// ## SUB

void DecodeSUBRegisterOrMemoryFromEither(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeD(1, decoding_context);
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeReg(instruction_input, 1, 3, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    DecodeOperandsRegisterOrMemoryAndEither(decoding_context);
    decoding_context->mnemonic = MNEMONIC_SUB;
}

void DecodeSUBImmediateFromAccumulator(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    DecodeOperandsAccumulatorAndImmediate(decoding_context);
    decoding_context->mnemonic = MNEMONIC_SUB;
}

// ## CMP

void DecodeCMPRegisterOrMemoryWithEither(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeD(1, decoding_context);
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeReg(instruction_input, 1, 3, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    DecodeOperandsRegisterOrMemoryAndEither(decoding_context);
    decoding_context->mnemonic = MNEMONIC_CMP;
}

void DecodeCMPImmediateWithAccumulator(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    DecodeOperandsAccumulatorAndImmediate(decoding_context);
    decoding_context->mnemonic = MNEMONIC_CMP;
}

// ## Return from CALL

void DecodeJO(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JO;
}

void DecodeJNO(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JNO;
}

void DecodeJB_JNAE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JB_JNAE;
}

void DecodeJNB_JAE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JNB_JAE;
}

void DecodeJE_JZ(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JE_JZ;
}

void DecodeJNE_JNZ(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JNE_JNZ;
}

void DecodeJBE_JNA(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JBE_JNA;
}

void DecodeJNBE_JA(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JNBE_JA;
}

void DecodeJS(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JS;
}

void DecodeJNS(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JNS;
}

void DecodeJP_JPE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JP_JPE;
}

void DecodeJNP_JPO(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JNP_JPO;
}

void DecodeJL_JNGE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JL_JNGE;
}

void DecodeJNL_JGE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JNL_JGE;
}

void DecodeJLE_JNG(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JLE_JNG;
}

void DecodeJNLE_JG(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JNLE_JG;
}

void DecodeLOOPNZ_LOOPNE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_LOOPNZ_LOOPNE;
}

void DecodeLOOPZ_LOOPE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_LOOPZ_LOOPE;
}

void DecodeLOOP(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_LOOP;
}

void DecodeJCXZ(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    DecodeOperandsReturnFromCall(decoding_context);
    decoding_context->mnemonic = MNEMONIC_JCXZ;
}

inst_decoder_t INSTRUCTION_DECODERS[256] = {
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

void DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    const inst_decoder_t instruction_decoder = INSTRUCTION_DECODERS[decoding_context->bytes[0]];
    instruction_decoder(instruction_input, decoding_context);
}
