void DecodeOperandsRegisterOrMemoryAndEither(Instruction *instruction, DecodingContext *decoding_context);
void DecodeOperandLabelLikeDisplacement(Operand *operand, DecodingContext *decoding_context);
void DecodeOperandRegisterOrMemoryAddress(Operand *operand, DecodingContext *decoding_context);
void DecodeOperandRegister(Operand *operand, DecodingContext *decoding_context);
void DecodeOperandSegmentRegister(Operand *operand, DecodingContext *decoding_context);
void DecodeOperandImmediate(Operand *operand, DecodingContext *decoding_context);
void DecodeOperandAccumulator(Operand *operand, DecodingContext *decoding_context);
void DecodeOperandDirectAddress(Operand *operand, DecodingContext *decoding_context);
