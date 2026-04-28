namespace cpu::instruction_decoding::context
{
    using memory::Memory;
    using cpu::core::CpuState;

    void ReadNextInstructionByte(DecodingContext *decoding_context, uint16_t ip_value, Memory *memory)
    {
        decoding_context->bytes[decoding_context->num_bytes_read] = memory->ReadMemory(
            (uint32_t) (ip_value + decoding_context->num_bytes_read), false);
        ++decoding_context->num_bytes_read;
    }

    void ReadNextInstructionBytesUpToIdx(DecodingContext *decoding_context,
                                         uint8_t byte_idx,
                                         uint16_t ip_value,
                                         Memory *memory)
    {
        while (decoding_context->num_bytes_read <= byte_idx)
        {
            ReadNextInstructionByte(decoding_context, ip_value, memory);
        }
    }
}
