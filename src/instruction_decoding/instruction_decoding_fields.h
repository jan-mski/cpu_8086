#ifndef INSTRUCTION_DECODING_FIELDS_H
#define INSTRUCTION_DECODING_FIELDS_H

namespace instruction_decoding::fields
{
    void DecodeByteFields(specs::FieldSpec* byte_field_specs,
                          U8 byte_idx,
                          context::DecodingContext* decoding_context,
                          memory::Memory* memory);
}

#endif // INSTRUCTION_DECODING_FIELDS_H
