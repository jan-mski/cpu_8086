typedef Instruction (*inst_decoder_t)(InstructionInput *instruction_input, DecodingContext *decoding_context);

Instruction DecodeUnsupported(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    return {};
}

// # MOV

Instruction DecodeMOVRegisterOrMemoryToEither(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeD(1, decoding_context);
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeReg(instruction_input, 1, 3, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandsRegisterOrMemoryAndEither(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeMOVMemoryToAccumulator(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeAddr(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandsAccumulatorAndMemory(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeMOVAccumulatorToMemory(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeAddr(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandsMemoryAndAccumulator(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeMOVImmediateToRegister(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(3, decoding_context);
    DecodeReg(instruction_input, 0, 0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandsRegisterAndImmediate(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeMOVImmediateToRegisterOrMemory(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    uint8_t num_bytes_read = DecodeDisplacement(instruction_input, decoding_context);
    DecodeData(instruction_input, 2 + num_bytes_read, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandsRegisterOrMemoryAndImmediate(&instruction, decoding_context);
    
    return instruction;
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

Instruction DecodeSignedArithmeticImmediateAndRegisterOrMemory(InstructionInput *instruction_input,
                                                        DecodingContext *decoding_context)
{
    DecodeS(1, decoding_context);
    DecodeArithmeticMnemonic(instruction_input, decoding_context);

    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    uint8_t num_bytes_read = DecodeDisplacement(instruction_input, decoding_context);
    DecodeData(instruction_input, 2 + num_bytes_read, decoding_context);

    Instruction instruction = {SIGNED_ARITHMETIC_MNEMONICS[decoding_context->common_mnemonic]};
    DecodeOperandsRegisterOrMemoryAndImmediate(&instruction, decoding_context);
    
    return instruction;
}

// ## ADD

Instruction DecodeADDRegisterOrMemoryToEither(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeD(1, decoding_context);
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeReg(instruction_input, 1, 3, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_ADD};
    DecodeOperandsRegisterOrMemoryAndEither(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeADDImmediateToAccumulator(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_ADD};
    DecodeOperandsAccumulatorAndImmediate(&instruction, decoding_context);
    
    return instruction;
}

// ## SUB

Instruction DecodeSUBRegisterOrMemoryFromEither(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeD(1, decoding_context);
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeReg(instruction_input, 1, 3, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_SUB};
    DecodeOperandsRegisterOrMemoryAndEither(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeSUBImmediateFromAccumulator(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_SUB};
    DecodeOperandsAccumulatorAndImmediate(&instruction, decoding_context);
    
    return instruction;
}

// ## CMP

Instruction DecodeCMPRegisterOrMemoryWithEither(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeD(1, decoding_context);
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeReg(instruction_input, 1, 3, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_CMP};
    DecodeOperandsRegisterOrMemoryAndEither(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeCMPImmediateWithAccumulator(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_CMP};
    DecodeOperandsAccumulatorAndImmediate(&instruction, decoding_context);
    
    return instruction;
}

// ## Return from CALL

Instruction DecodeJO(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JO};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJNO(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JNO};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJB_JNAE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JB_JNAE};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJNB_JAE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JNB_JAE};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJE_JZ(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JE_JZ};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJNE_JNZ(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JNE_JNZ};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJBE_JNA(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JBE_JNA};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJNBE_JA(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JNBE_JA};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJS(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JS};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJNS(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JNS};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJP_JPE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JP_JPE};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJNP_JPO(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JNP_JPO};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJL_JNGE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JL_JNGE};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJNL_JGE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JNL_JGE};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJLE_JNG(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JLE_JNG};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJNLE_JG(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JNLE_JG};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeLOOPNZ_LOOPNE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_LOOPNZ_LOOPNE};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeLOOPZ_LOOPE(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_LOOPZ_LOOPE};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeLOOP(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_LOOP};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
}

Instruction DecodeJCXZ(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_JCXZ};
    DecodeOperandsReturnFromCall(&instruction, decoding_context);
    
    return instruction;
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

Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    inst_decoder_t instruction_decoder = INSTRUCTION_DECODERS[decoding_context->bytes[0]];
    
    return instruction_decoder(instruction_input, decoding_context);
}
