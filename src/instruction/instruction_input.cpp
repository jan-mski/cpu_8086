size_t ReadNextByte(InstructionInput *instruction_input, InstructionDecodingContext *decoding_context)
{
    FILE *stream = instruction_input->stream;
    if (!stream)
    {
        return 0;
    }

    const size_t num_bytes_read = fread(decoding_context->bytes + decoding_context->num_bytes_read, sizeof(uint8_t), 1, stream);
    decoding_context->num_bytes_read += num_bytes_read;

    return num_bytes_read;
}

void ReadNextBytesToIndex(InstructionInput *instruction_input,
                          InstructionDecodingContext *decoding_context,
                          const uint8_t byte_index)
{
    while (decoding_context->num_bytes_read <= byte_index)
    {
        ReadNextByte(instruction_input, decoding_context);
    }
}