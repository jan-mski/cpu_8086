#ifndef INSTRUCTION_DECODING_CONTEXT_H
#define INSTRUCTION_DECODING_CONTEXT_H

namespace instruction_decoding::context
{
    struct DecodingContext
    {
        U8 bytes[6];
        U8 num_bytes_read;
        bool d;                    // 1 bit
        bool s;                    // 1 bit
        bool v;                    // 1 bit
        bool w;                    // 1 bit
        bool is_w_forced;
        U8 mod;                    // 2 bits
        U8 sr;                     // 2 bits
        U8 reg;                    // 3 bits
        U8 r_m;                    // 3 bits
        U8 opcode_extension;       // 3 bits
        U16 data;                  // 8 || 16 bits
        U16 addr;                  // 8 || 16 bits
        I32 displacement;          // 8 || 16 bits
        I16 ip_increment;          // 16 bits
    };

    void ReadNextInstructionByte(DecodingContext* decoding_context,
                                 U16 ip_value,
                                 memory::Memory* memory);
}

#endif //INSTRUCTION_DECODING_CONTEXT_H
