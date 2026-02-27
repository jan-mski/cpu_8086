Instruction DecodeUnsupported(InstructionInput *instruction_input,
                              DecodingContext *decoding_context,
                              InstructionSpec instruction_spec)
{
    return {};
}

// # MOV

Instruction DecodeMOVRegisterOrMemoryToEither(InstructionInput *instruction_input,
                                              DecodingContext *decoding_context,
                                              InstructionSpec instruction_spec)
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
                                         InstructionSpec instruction_spec)
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
                                         InstructionSpec instruction_spec)
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
                                         InstructionSpec instruction_spec)
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
                                                 InstructionSpec instruction_spec)
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
                                                               InstructionSpec instruction_spec)
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
                                              InstructionSpec instruction_spec)
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
                                            InstructionSpec instruction_spec)
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
                                                InstructionSpec instruction_spec)
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
                                              InstructionSpec instruction_spec)
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
                                                InstructionSpec instruction_spec)
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
                                              InstructionSpec instruction_spec)
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
                                 InstructionSpec instruction_spec)
{
    DecodeDisplacement8Bit(instruction_input, 1, decoding_context);

    Instruction instruction = {instruction_spec.mnemonic};
    DecodeOperandLabelLikeDisplacement(&instruction.operands[0], decoding_context);

    return instruction;
}

// ## PUSH, POP

Instruction DecodeStackOperationRegisterOrMemory(InstructionInput *instruction_input,
                                                 DecodingContext *decoding_context,
                                                 InstructionSpec instruction_spec)
{
    DecodeModAndRM(instruction_input, 6, 0, decoding_context);
    DecodeDisplacement(instruction_input, decoding_context);

    Instruction instruction = {instruction_spec.mnemonic};
    DecodeOperandRegisterOrMemoryAddress(&instruction.operands[0], decoding_context, true);

    return instruction;
}

Instruction DecodeStackOperationRegister(InstructionInput *instruction_input,
                                         DecodingContext *decoding_context,
                                         InstructionSpec instruction_spec)
{
    DecodeReg(instruction_input, 0, 0, decoding_context);

    Instruction instruction = {instruction_spec.mnemonic};
    DecodeOperandRegister(&instruction.operands[0], decoding_context, true);

    return instruction;
}

Instruction DecodeStackOperationSegmentRegister(InstructionInput *instruction_input,
                                                DecodingContext *decoding_context,
                                                InstructionSpec instruction_spec)
{
    DecodeSR(instruction_input, 0, 3, decoding_context);

    Instruction instruction = {instruction_spec.mnemonic};
    DecodeOperandSegmentRegister(&instruction.operands[0], decoding_context);

    return instruction;
}

InstructionDecodeSpec INSTRUCTION_DECODE_SPECS[256] = {};

void InitializeInstructionDecodeSpecs()
{
    INSTRUCTION_DECODE_SPECS[0b00000000] = {DecodeADDRegisterOrMemoryToEither};
    INSTRUCTION_DECODE_SPECS[0b00000001] = {DecodeADDRegisterOrMemoryToEither};
    INSTRUCTION_DECODE_SPECS[0b00000010] = {DecodeADDRegisterOrMemoryToEither};
    INSTRUCTION_DECODE_SPECS[0b00000011] = {DecodeADDRegisterOrMemoryToEither};

    INSTRUCTION_DECODE_SPECS[0b00000100] = {DecodeADDImmediateToAccumulator};
    INSTRUCTION_DECODE_SPECS[0b00000101] = {DecodeADDImmediateToAccumulator};

    INSTRUCTION_DECODE_SPECS[0b00000110] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00000111] = {DecodeStackOperationSegmentRegister, MNEMONIC_POP};

    INSTRUCTION_DECODE_SPECS[0b00001000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00001001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00001010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00001011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00001100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00001101] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b00001110] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00001111] = {DecodeStackOperationSegmentRegister, MNEMONIC_POP};

    INSTRUCTION_DECODE_SPECS[0b00010000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00010001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00010010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00010011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00010100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00010101] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b00010110] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00010111] = {DecodeStackOperationSegmentRegister, MNEMONIC_POP};

    INSTRUCTION_DECODE_SPECS[0b00011000] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00011001] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00011010] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00011011] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00011100] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00011101] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b00011110] = {DecodeStackOperationSegmentRegister, MNEMONIC_PUSH};

    INSTRUCTION_DECODE_SPECS[0b00011111] = {DecodeStackOperationSegmentRegister, MNEMONIC_POP};

    INSTRUCTION_DECODE_SPECS[0b00100000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00100001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00100010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00100011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00100100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00100101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00100110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00100111] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b00101000] = {DecodeSUBRegisterOrMemoryFromEither};
    INSTRUCTION_DECODE_SPECS[0b00101001] = {DecodeSUBRegisterOrMemoryFromEither};
    INSTRUCTION_DECODE_SPECS[0b00101010] = {DecodeSUBRegisterOrMemoryFromEither};
    INSTRUCTION_DECODE_SPECS[0b00101011] = {DecodeSUBRegisterOrMemoryFromEither};

    INSTRUCTION_DECODE_SPECS[0b00101100] = {DecodeSUBImmediateFromAccumulator};
    INSTRUCTION_DECODE_SPECS[0b00101101] = {DecodeSUBImmediateFromAccumulator};

    INSTRUCTION_DECODE_SPECS[0b00101110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00101111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00110000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00110001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00110010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00110011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00110100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00110101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00110110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00110111] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b00111000] = {DecodeCMPRegisterOrMemoryWithEither};
    INSTRUCTION_DECODE_SPECS[0b00111001] = {DecodeCMPRegisterOrMemoryWithEither};
    INSTRUCTION_DECODE_SPECS[0b00111010] = {DecodeCMPRegisterOrMemoryWithEither};
    INSTRUCTION_DECODE_SPECS[0b00111011] = {DecodeCMPRegisterOrMemoryWithEither};

    INSTRUCTION_DECODE_SPECS[0b00111100] = {DecodeCMPImmediateWithAccumulator};
    INSTRUCTION_DECODE_SPECS[0b00111101] = {DecodeCMPImmediateWithAccumulator};

    INSTRUCTION_DECODE_SPECS[0b00111110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b00111111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01000000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01000001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01000010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01000011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01000100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01000101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01000110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01000111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01001000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01001001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01001010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01001011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01001100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01001101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01001110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01001111] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b01010000] = {DecodeStackOperationRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b01010001] = {DecodeStackOperationRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b01010010] = {DecodeStackOperationRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b01010011] = {DecodeStackOperationRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b01010100] = {DecodeStackOperationRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b01010101] = {DecodeStackOperationRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b01010110] = {DecodeStackOperationRegister, MNEMONIC_PUSH};
    INSTRUCTION_DECODE_SPECS[0b01010111] = {DecodeStackOperationRegister, MNEMONIC_PUSH};

    INSTRUCTION_DECODE_SPECS[0b01011000] = {DecodeStackOperationRegister, MNEMONIC_POP};
    INSTRUCTION_DECODE_SPECS[0b01011001] = {DecodeStackOperationRegister, MNEMONIC_POP};
    INSTRUCTION_DECODE_SPECS[0b01011010] = {DecodeStackOperationRegister, MNEMONIC_POP};
    INSTRUCTION_DECODE_SPECS[0b01011011] = {DecodeStackOperationRegister, MNEMONIC_POP};
    INSTRUCTION_DECODE_SPECS[0b01011100] = {DecodeStackOperationRegister, MNEMONIC_POP};
    INSTRUCTION_DECODE_SPECS[0b01011101] = {DecodeStackOperationRegister, MNEMONIC_POP};
    INSTRUCTION_DECODE_SPECS[0b01011110] = {DecodeStackOperationRegister, MNEMONIC_POP};
    INSTRUCTION_DECODE_SPECS[0b01011111] = {DecodeStackOperationRegister, MNEMONIC_POP};

    INSTRUCTION_DECODE_SPECS[0b01100000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01100001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01100010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01100011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01100100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01100101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01100110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01100111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01101000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01101001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01101010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01101011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01101100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01101101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01101110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b01101111] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b01110000] = {DecodeReturnFromCall, MNEMONIC_JO};
    INSTRUCTION_DECODE_SPECS[0b01110001] = {DecodeReturnFromCall, MNEMONIC_JNO};
    INSTRUCTION_DECODE_SPECS[0b01110010] = {DecodeReturnFromCall, MNEMONIC_JB_JNAE};
    INSTRUCTION_DECODE_SPECS[0b01110011] = {DecodeReturnFromCall, MNEMONIC_JNB_JAE};
    INSTRUCTION_DECODE_SPECS[0b01110100] = {DecodeReturnFromCall, MNEMONIC_JE_JZ};
    INSTRUCTION_DECODE_SPECS[0b01110101] = {DecodeReturnFromCall, MNEMONIC_JNE_JNZ};
    INSTRUCTION_DECODE_SPECS[0b01110110] = {DecodeReturnFromCall, MNEMONIC_JBE_JNA};
    INSTRUCTION_DECODE_SPECS[0b01110111] = {DecodeReturnFromCall, MNEMONIC_JNBE_JA};
    INSTRUCTION_DECODE_SPECS[0b01111000] = {DecodeReturnFromCall, MNEMONIC_JS};
    INSTRUCTION_DECODE_SPECS[0b01111001] = {DecodeReturnFromCall, MNEMONIC_JNS};
    INSTRUCTION_DECODE_SPECS[0b01111010] = {DecodeReturnFromCall, MNEMONIC_JP_JPE};
    INSTRUCTION_DECODE_SPECS[0b01111011] = {DecodeReturnFromCall, MNEMONIC_JNP_JPO};
    INSTRUCTION_DECODE_SPECS[0b01111100] = {DecodeReturnFromCall, MNEMONIC_JL_JNGE};
    INSTRUCTION_DECODE_SPECS[0b01111101] = {DecodeReturnFromCall, MNEMONIC_JNL_JGE};
    INSTRUCTION_DECODE_SPECS[0b01111110] = {DecodeReturnFromCall, MNEMONIC_JLE_JNG};
    INSTRUCTION_DECODE_SPECS[0b01111111] = {DecodeReturnFromCall, MNEMONIC_JNLE_JG};

    INSTRUCTION_DECODE_SPECS[0b10000000] = {DecodeSignedArithmeticImmediateAndRegisterOrMemory};
    INSTRUCTION_DECODE_SPECS[0b10000001] = {DecodeSignedArithmeticImmediateAndRegisterOrMemory};
    INSTRUCTION_DECODE_SPECS[0b10000010] = {DecodeSignedArithmeticImmediateAndRegisterOrMemory};
    INSTRUCTION_DECODE_SPECS[0b10000011] = {DecodeSignedArithmeticImmediateAndRegisterOrMemory};

    INSTRUCTION_DECODE_SPECS[0b10000100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10000101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10000110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10000111] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b10001000] = {DecodeMOVRegisterOrMemoryToEither};
    INSTRUCTION_DECODE_SPECS[0b10001001] = {DecodeMOVRegisterOrMemoryToEither};
    INSTRUCTION_DECODE_SPECS[0b10001010] = {DecodeMOVRegisterOrMemoryToEither};
    INSTRUCTION_DECODE_SPECS[0b10001011] = {DecodeMOVRegisterOrMemoryToEither};

    INSTRUCTION_DECODE_SPECS[0b10001100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10001101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10001110] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b10001111] = {DecodeStackOperationRegisterOrMemory, MNEMONIC_POP};

    INSTRUCTION_DECODE_SPECS[0b10010000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10010001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10010010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10010011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10010100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10010101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10010110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10010111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10011000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10011001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10011010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10011011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10011100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10011101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10011110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10011111] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b10100000] = {DecodeMOVMemoryToAccumulator};
    INSTRUCTION_DECODE_SPECS[0b10100001] = {DecodeMOVMemoryToAccumulator};

    INSTRUCTION_DECODE_SPECS[0b10100010] = {DecodeMOVAccumulatorToMemory};
    INSTRUCTION_DECODE_SPECS[0b10100011] = {DecodeMOVAccumulatorToMemory};

    INSTRUCTION_DECODE_SPECS[0b10100100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10100101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10100110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10100111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10101000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10101001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10101010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10101011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10101100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10101101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10101110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b10101111] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b10110000] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10110001] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10110010] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10110011] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10110100] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10110101] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10110110] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10110111] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10111000] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10111001] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10111010] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10111011] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10111100] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10111101] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10111110] = {DecodeMOVImmediateToRegister};
    INSTRUCTION_DECODE_SPECS[0b10111111] = {DecodeMOVImmediateToRegister};

    INSTRUCTION_DECODE_SPECS[0b11000000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11000001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11000010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11000011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11000100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11000101] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b11000110] = {DecodeMOVImmediateToRegisterOrMemory};
    INSTRUCTION_DECODE_SPECS[0b11000111] = {DecodeMOVImmediateToRegisterOrMemory};

    INSTRUCTION_DECODE_SPECS[0b11001000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11001001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11001010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11001011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11001100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11001101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11001110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11001111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11010000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11010001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11010010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11010011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11010100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11010101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11010110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11010111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11011000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11011001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11011010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11011011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11011100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11011101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11011110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11011111] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b11100000] = {DecodeReturnFromCall, MNEMONIC_LOOPNZ_LOOPNE};
    INSTRUCTION_DECODE_SPECS[0b11100001] = {DecodeReturnFromCall, MNEMONIC_LOOPZ_LOOPE};
    INSTRUCTION_DECODE_SPECS[0b11100010] = {DecodeReturnFromCall, MNEMONIC_LOOP};
    INSTRUCTION_DECODE_SPECS[0b11100011] = {DecodeReturnFromCall, MNEMONIC_JCXZ};

    INSTRUCTION_DECODE_SPECS[0b11100100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11100101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11100110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11100111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11101000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11101001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11101010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11101011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11101100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11101101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11101110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11101111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11110000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11110001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11110010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11110011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11110100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11110101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11110110] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11110111] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11111000] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11111001] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11111010] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11111011] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11111100] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11111101] = {DecodeUnsupported};
    INSTRUCTION_DECODE_SPECS[0b11111110] = {DecodeUnsupported};

    INSTRUCTION_DECODE_SPECS[0b11111111] = {DecodeStackOperationRegisterOrMemory, MNEMONIC_PUSH};
}

Instruction DecodeInstruction(InstructionInput *instruction_input,
                              DecodingContext *decoding_context)
{
    InstructionDecodeSpec spec = INSTRUCTION_DECODE_SPECS[decoding_context->bytes[0]];

    return spec.decoder_function(instruction_input, decoding_context, spec.instruction_spec);
}
