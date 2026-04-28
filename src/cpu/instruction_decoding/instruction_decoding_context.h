#ifndef CPU_INSTRUCTION_DECODING_CONTEXT_H
#define CPU_INSTRUCTION_DECODING_CONTEXT_H

namespace cpu::instruction_decoding::context
{
    struct DecodingContext
    {
        uint8_t bytes[6];
        uint8_t num_bytes_read;
        bool d;                    // 1 bit
        bool s;                    // 1 bit
        bool v;                    // 1 bit
        bool w;                    // 1 bit
        bool is_w_forced;
        uint8_t mod;               // 2 bits
        uint8_t sr;                // 2 bits
        uint8_t reg;               // 3 bits
        uint8_t r_m;               // 3 bits
        uint8_t opcode_extension;  // 3 bits
        uint16_t data;             // 8 || 16 bits
        uint16_t addr;             // 8 || 16 bits
        int32_t displacement;      // 8 || 16 bits
        int16_t ip_increment;      // 16 bits
    };

    void ReadNextInstructionByte(DecodingContext *decoding_context, uint16_t ip_value, memory::Memory *memory);
}

#endif //CPU_INSTRUCTION_DECODING_CONTEXT_H
