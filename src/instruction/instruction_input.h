struct InstructionInput
{
    FILE *stream;
};

size_t ReadNextByte(InstructionInput *instruction_input, InstructionDecodingContext *decoding_context);
void ReadNextBytesToIndex(InstructionInput *instruction_input, InstructionDecodingContext *decoding_context, uint8_t byte_index);
