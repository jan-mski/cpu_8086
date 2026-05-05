namespace instruction_decoding::context
{
    namespace mem = ::memory;

    void ReadNextInstructionByte(DecodingContext* decoding_context,
                                 U16 ip_value,
                                 mem::Memory* memory)
    {
        mem::Address address = (mem::Address) (ip_value + decoding_context->num_bytes_read);
        decoding_context->bytes[decoding_context->num_bytes_read] = mem::ReadByte(memory, address);
        ++decoding_context->num_bytes_read;
    }

    void ReadNextInstructionBytesUpToIdx(DecodingContext* decoding_context,
                                         U8 byte_idx,
                                         U16 ip_value,
                                         mem::Memory* memory)
    {
        while (decoding_context->num_bytes_read <= byte_idx)
        {
            ReadNextInstructionByte(decoding_context, ip_value, memory);
        }
    }
}
