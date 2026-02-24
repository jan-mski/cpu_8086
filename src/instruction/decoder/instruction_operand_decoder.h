void DecodeOperandsRegisterOrMemoryAndEither(Instruction *instruction, DecodingContext *decoding_context);
void DecodeOperandsRegisterOrMemoryAndImmediate(Instruction *instruction, DecodingContext *decoding_context);
void DecodeOperandsRegisterAndImmediate(Instruction *instruction, DecodingContext *decoding_context);
void DecodeOperandsAccumulatorAndMemory(Instruction *instruction, DecodingContext *decoding_context);
void DecodeOperandsMemoryAndAccumulator(Instruction *instruction, DecodingContext *decoding_context);
void DecodeOperandsAccumulatorAndImmediate(Instruction *instruction, DecodingContext *decoding_context);
void DecodeOperandsReturnFromCall(Instruction *instruction, DecodingContext *decoding_context);
