uint8_t DecodeField(FieldSpec field_spec, uint8_t byte_idx, InstructionInput *instruction_input,
                    DecodingContext *decoding_context);
uint8_t DecodeByte(InstructionInput *instruction_input, DecodingContext *decoding_context);
int32_t DecodeDataHighByte(InstructionInput *instruction_input, DecodingContext *decoding_context);
int32_t DecodeAddrHighByte(InstructionInput *instruction_input, DecodingContext *decoding_context);
int32_t DecodeDisplacement8Bit(InstructionInput *instruction_input, DecodingContext *decoding_context);
int32_t DecodeDisplacement16Bit(InstructionInput *instruction_input, DecodingContext *decoding_context);
int32_t DecodeDisplacement(InstructionInput *instruction_input, DecodingContext *decoding_context);
