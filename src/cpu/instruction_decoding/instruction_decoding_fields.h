#ifndef CPU_INSTRUCTION_DECODING_FIELDS_H
#define CPU_INSTRUCTION_DECODING_FIELDS_H

namespace cpu::instruction_decoding::fields
{
    void DecodeByteFields(specs::FieldSpec *byte_field_specs,
                          uint8_t byte_idx,
                          context::DecodingContext *decoding_context,
                          memory::Memory *memory);
}

#endif // CPU_INSTRUCTION_DECODING_FIELDS_H
