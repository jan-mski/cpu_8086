size_t ReadNextByte(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    if (!instruction_input->stream)
    {
        return 0;
    }

    size_t num_bytes_read = fread(decoding_context->bytes + decoding_context->num_bytes_read, sizeof(uint8_t), 1,
                                  instruction_input->stream);
    decoding_context->num_bytes_read += num_bytes_read;

    return num_bytes_read;
}

void ReadBytesUpToIdx(InstructionInput *instruction_input, DecodingContext *decoding_context, uint8_t byte_idx)
{
    while (decoding_context->num_bytes_read <= byte_idx)
    {
        ReadNextByte(instruction_input, decoding_context);
    }
}