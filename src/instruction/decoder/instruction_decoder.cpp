Instruction DecodeUnsupported(InstructionInput *instruction_input,
                              DecodingContext *decoding_context,
                              DecoderFunctionArgs decoder_function_args)
{
    return {};
}

// # MOV

Instruction DecodeMOVRegisterOrMemoryToEither(InstructionInput *instruction_input,
                                              DecodingContext *decoding_context,
                                              DecoderFunctionArgs decoder_function_args)
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

Instruction DecodeMOVMemoryToAccumulator(InstructionInput *instruction_input,
                                         DecodingContext *decoding_context,
                                         DecoderFunctionArgs decoder_function_args)
{
    DecodeW(0, decoding_context);
    DecodeAddr(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandAccumulator(&instruction.operands[0], decoding_context);
    DecodeOperandDirectAddress(&instruction.operands[1], decoding_context);

    return instruction;
}

Instruction DecodeMOVAccumulatorToMemory(InstructionInput *instruction_input,
                                         DecodingContext *decoding_context,
                                         DecoderFunctionArgs decoder_function_args)
{
    DecodeW(0, decoding_context);
    DecodeAddr(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandDirectAddress(&instruction.operands[0], decoding_context);
    DecodeOperandAccumulator(&instruction.operands[1], decoding_context);

    return instruction;
}

Instruction DecodeMOVImmediateToRegister(InstructionInput *instruction_input,
                                         DecodingContext *decoding_context,
                                         DecoderFunctionArgs decoder_function_args)
{
    DecodeW(3, decoding_context);
    DecodeReg(instruction_input, 0, 0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandRegister(&instruction.operands[0], decoding_context);
    DecodeOperandImmediate(&instruction.operands[1], decoding_context);

    return instruction;
}

Instruction DecodeMOVImmediateToRegisterOrMemory(InstructionInput *instruction_input,
                                                 DecodingContext *decoding_context,
                                                 DecoderFunctionArgs decoder_function_args)
{
    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    uint8_t num_bytes_read = DecodeDisplacement(instruction_input, decoding_context);
    DecodeData(instruction_input, 2 + num_bytes_read, decoding_context);

    Instruction instruction = {MNEMONIC_MOV};
    DecodeOperandRegisterOrMemoryAddress(&instruction.operands[0], decoding_context);
    DecodeOperandImmediate(&instruction.operands[1], decoding_context);

    return instruction;
}

// # Arithmetic
Mnemonic SIGNED_ARITHMETIC_MNEMONICS[] = {
    MNEMONIC_ADD,
    MNEMONIC_NONE,
    MNEMONIC_NONE, // "adc" - unsupported
    MNEMONIC_NONE, // "sbb"
    MNEMONIC_NONE,
    MNEMONIC_SUB,
    MNEMONIC_NONE,
    MNEMONIC_CMP
};

Instruction DecodeSignedArithmeticImmediateAndRegisterOrMemory(InstructionInput *instruction_input,
                                                               DecodingContext *decoding_context,
                                                               DecoderFunctionArgs decoder_function_args)
{
    DecodeS(1, decoding_context);
    DecodeArithmeticMnemonic(instruction_input, decoding_context);

    DecodeW(0, decoding_context);
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    uint8_t num_bytes_read = DecodeDisplacement(instruction_input, decoding_context);
    DecodeData(instruction_input, 2 + num_bytes_read, decoding_context);

    Instruction instruction = {SIGNED_ARITHMETIC_MNEMONICS[decoding_context->common_mnemonic]};
    DecodeOperandRegisterOrMemoryAddress(&instruction.operands[0], decoding_context);
    DecodeOperandImmediate(&instruction.operands[1], decoding_context);

    return instruction;
}

// ## ADD

Instruction DecodeADDRegisterOrMemoryToEither(InstructionInput *instruction_input,
                                              DecodingContext *decoding_context,
                                              DecoderFunctionArgs decoder_function_args)
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

Instruction DecodeADDImmediateToAccumulator(InstructionInput *instruction_input,
                                            DecodingContext *decoding_context,
                                            DecoderFunctionArgs decoder_function_args)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_ADD};
    DecodeOperandAccumulator(&instruction.operands[0], decoding_context);
    DecodeOperandImmediate(&instruction.operands[1], decoding_context);

    return instruction;
}

// ## SUB

Instruction DecodeSUBRegisterOrMemoryFromEither(InstructionInput *instruction_input,
                                                DecodingContext *decoding_context,
                                                DecoderFunctionArgs decoder_function_args)
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

Instruction DecodeSUBImmediateFromAccumulator(InstructionInput *instruction_input,
                                              DecodingContext *decoding_context,
                                              DecoderFunctionArgs decoder_function_args)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_SUB};
    DecodeOperandAccumulator(&instruction.operands[0], decoding_context);
    DecodeOperandImmediate(&instruction.operands[1], decoding_context);

    return instruction;
}

// ## CMP

Instruction DecodeCMPRegisterOrMemoryWithEither(InstructionInput *instruction_input,
                                                DecodingContext *decoding_context,
                                                DecoderFunctionArgs decoder_function_args)
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

Instruction DecodeCMPImmediateWithAccumulator(InstructionInput *instruction_input,
                                              DecodingContext *decoding_context,
                                              DecoderFunctionArgs decoder_function_args)
{
    DecodeW(0, decoding_context);
    DecodeData(instruction_input, 1, decoding_context);

    Instruction instruction = {MNEMONIC_CMP};
    DecodeOperandAccumulator(&instruction.operands[0], decoding_context);
    DecodeOperandImmediate(&instruction.operands[1], decoding_context);

    return instruction;
}

// ## Return from CALL

Instruction DecodeReturnFromCall(InstructionInput *instruction_input,
                                 DecodingContext *decoding_context,
                                 DecoderFunctionArgs decoder_function_args)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {decoder_function_args.mnemonic};
    DecodeOperandLabelLikeDisplacement(&instruction.operands[0], decoding_context);

    return instruction;
}

// ## PUSH

Instruction DecodePUSHRegisterOrMemory(InstructionInput *instruction_input,
                                       DecodingContext *decoding_context,
                                       DecoderFunctionArgs decoder_function_args)
{
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    Instruction instruction = {MNEMONIC_PUSH};
    DecodeOperandRegisterOrMemoryAddress(&instruction.operands[0], decoding_context, true);

    return instruction;
}

Instruction DecodePUSHRegister(InstructionInput *instruction_input,
                               DecodingContext *decoding_context,
                               DecoderFunctionArgs decoder_function_args)
{
    DecodeReg(instruction_input, 0, 0, decoding_context);

    Instruction instruction = {MNEMONIC_PUSH};
    DecodeOperandRegister(&instruction.operands[0], decoding_context, true);

    return instruction;
}


InstructionDecodeSpec INSTRUCTION_DECODE_SPECS[256] = {
    /* 00000000 - 00000011 [  0 -   3] */ REPEAT_4({DecodeADDRegisterOrMemoryToEither}),
    /* 00000100 - 00000101 [  4 -   5] */ REPEAT_2({DecodeADDImmediateToAccumulator}),
    /* 00000110 - 00100111 [  6 -  39] */ REPEAT_34({DecodeUnsupported}),
    /* 00101000 - 00101011 [ 40 -  43] */ REPEAT_4({DecodeSUBRegisterOrMemoryFromEither}),
    /* 00101100 - 00101101 [ 44 -  45] */ REPEAT_2({DecodeSUBImmediateFromAccumulator}),
    /* 00101110 - 00110111 [ 46 -  55] */ REPEAT_10({DecodeUnsupported}),
    /* 00111000 - 00111011 [ 56 -  59] */ REPEAT_4({DecodeCMPRegisterOrMemoryWithEither}),
    /* 00111100 - 00111101 [ 60 -  61] */ REPEAT_2({DecodeCMPImmediateWithAccumulator}),
    /* 00111110 - 01101111 [ 62 -  79] */ REPEAT_18({DecodeUnsupported}),
    /* 01010000 - 01010111 [ 80 -  87] */ REPEAT_8({DecodePUSHRegister}),
    /* 00111110 - 01101111 [ 88 - 111] */ REPEAT_24({DecodeUnsupported}),
    /* 01110000 - 01110000 [112 - 112] */ {DecodeReturnFromCall, MNEMONIC_JO},
    /* 01110001 - 01110001 [113 - 113] */ {DecodeReturnFromCall, MNEMONIC_JNO},
    /* 01110010 - 01110010 [114 - 114] */ {DecodeReturnFromCall, MNEMONIC_JB_JNAE},
    /* 01110011 - 01110011 [115 - 115] */ {DecodeReturnFromCall, MNEMONIC_JNB_JAE},
    /* 01110100 - 01110100 [116 - 116] */ {DecodeReturnFromCall, MNEMONIC_JE_JZ},
    /* 01110101 - 01110101 [117 - 117] */ {DecodeReturnFromCall, MNEMONIC_JNE_JNZ},
    /* 01110110 - 01110110 [118 - 118] */ {DecodeReturnFromCall, MNEMONIC_JBE_JNA},
    /* 01110111 - 01110111 [119 - 119] */ {DecodeReturnFromCall, MNEMONIC_JNBE_JA},
    /* 01111000 - 01111000 [120 - 120] */ {DecodeReturnFromCall, MNEMONIC_JS},
    /* 01111001 - 01111001 [121 - 121] */ {DecodeReturnFromCall, MNEMONIC_JNS},
    /* 01111010 - 01111010 [122 - 122] */ {DecodeReturnFromCall, MNEMONIC_JP_JPE},
    /* 01111011 - 01111011 [123 - 123] */ {DecodeReturnFromCall, MNEMONIC_JNP_JPO},
    /* 01111100 - 01111100 [124 - 124] */ {DecodeReturnFromCall, MNEMONIC_JL_JNGE},
    /* 01111101 - 01111101 [125 - 125] */ {DecodeReturnFromCall, MNEMONIC_JNL_JGE},
    /* 01111110 - 01111110 [126 - 126] */ {DecodeReturnFromCall, MNEMONIC_JLE_JNG},
    /* 01111111 - 01111111 [127 - 127] */ {DecodeReturnFromCall, MNEMONIC_JNLE_JG},
    /* 10000000 - 10000011 [128 - 131] */ REPEAT_4({DecodeSignedArithmeticImmediateAndRegisterOrMemory}),
    /* 10000100 - 10000111 [132 - 135] */ REPEAT_4({DecodeUnsupported}),
    /* 10001000 - 10001011 [136 - 139] */ REPEAT_4({DecodeMOVRegisterOrMemoryToEither}),
    /* 10001100 - 10011111 [140 - 159] */ REPEAT_20({DecodeUnsupported}),
    /* 10100000 - 10100001 [160 - 161] */ REPEAT_2({DecodeMOVMemoryToAccumulator}),
    /* 10100010 - 10100011 [162 - 163] */ REPEAT_2({DecodeMOVAccumulatorToMemory}),
    /* 10100100 - 10101111 [164 - 175] */ REPEAT_12({DecodeUnsupported}),
    /* 10110000 - 10111111 [176 - 191] */ REPEAT_16({DecodeMOVImmediateToRegister}),
    /* 11000000 - 11000101 [192 - 197] */ REPEAT_6({DecodeUnsupported}),
    /* 11000110 - 11000111 [198 - 199] */ REPEAT_2({DecodeMOVImmediateToRegisterOrMemory}),
    /* 11001000 - 11011111 [200 - 223] */ REPEAT_24({DecodeUnsupported}),
    /* 11100000 - 11100000 [224 - 224] */ {DecodeReturnFromCall, MNEMONIC_LOOPNZ_LOOPNE},
    /* 11100001 - 11100001 [225 - 225] */ {DecodeReturnFromCall, MNEMONIC_LOOPZ_LOOPE},
    /* 11100010 - 11100010 [226 - 226] */ {DecodeReturnFromCall, MNEMONIC_LOOP},
    /* 11100011 - 11100011 [227 - 227] */ {DecodeReturnFromCall, MNEMONIC_JCXZ},
    /* 11100100 - 11111110 [228 - 254] */ REPEAT_27({DecodeUnsupported}),
    /* 11111111 - 11111111 [255 - 255] */ {DecodePUSHRegisterOrMemory}
};

Instruction DecodeInstruction(InstructionInput *instruction_input,
                              DecodingContext *decoding_context)
{
    InstructionDecodeSpec spec = INSTRUCTION_DECODE_SPECS[decoding_context->bytes[0]];

    return spec.decoder_function(instruction_input, decoding_context, spec.decoder_function_args);
}
