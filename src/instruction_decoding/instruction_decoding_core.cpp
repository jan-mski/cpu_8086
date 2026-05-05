namespace instruction_decoding::core
{
    namespace mem = ::memory;
    namespace cpu = ::cpu;
    namespace ins = ::instruction;
    namespace dec_ctx = ::instruction_decoding::context;
    namespace dec_fld = ::instruction_decoding::fields;
    namespace dec_opr = ::instruction_decoding::operands;
    namespace dec_spx = ::instruction_decoding::specs;

    ins::Instruction DecodeInstruction(dec_ctx::DecodingContext* decoding_context,
                                       dec_spx::InstructionSpecBody* instruction_spec_body)
    {
        ins::Instruction instruction = {};

        dec_opr::DecodeOperands(&instruction, instruction_spec_body->format.operand_types, decoding_context);
        instruction.mnemonic = instruction_spec_body->format.mnemonic;
        instruction.is_wide = decoding_context->w;

        return instruction;
    }

    ins::Instruction DecodeInstruction(dec_spx::InstructionSpec* instruction_spec,
                                       dec_ctx::DecodingContext* decoding_context,
                                       cpu::CpuState* cpu_state,
                                       mem::Memory* memory)
    {
        ins::Instruction instruction = {};
        dec_spx::InstructionSpecBody instruction_spec_body = {};

        switch (instruction_spec->type)
        {
            case dec_spx::InstructionSpecType_None:
            {
            } break;
            case dec_spx::InstructionSpecType_Regular:
            {
                instruction_spec_body = instruction_spec->bodies[0];
                dec_fld::DecodeByteFields(instruction_spec_body.byte_1, 0, decoding_context, cpu_state, memory);
                dec_fld::DecodeByteFields(instruction_spec_body.byte_2, 1, decoding_context, cpu_state, memory);
                dec_fld::DecodeByteFields(instruction_spec_body.byte_3456, 2, decoding_context, cpu_state, memory);
                instruction = DecodeInstruction(decoding_context, &instruction_spec_body);
            } break;
            case dec_spx::InstructionSpecType_ExtendedOpcode:
            {
                dec_fld::DecodeByteFields(dec_spx::OPCODE_EXT_BYTE_FIELDS, 1, decoding_context, cpu_state, memory);

                instruction_spec_body = instruction_spec->bodies[decoding_context->opcode_extension];
                dec_fld::DecodeByteFields(instruction_spec_body.byte_1, 0, decoding_context, cpu_state, memory);
                dec_fld::DecodeByteFields(instruction_spec_body.byte_3456, 2, decoding_context, cpu_state, memory);
                instruction = DecodeInstruction(decoding_context, &instruction_spec_body);
            } break;
        }

        return instruction;
    }

    ins::Instruction DecodeInstruction(dec_ctx::DecodingContext* decoding_context,
                                       cpu::CpuState* cpu_state,
                                       mem::Memory* memory)
    {
        dec_spx::InstructionSpec instruction_spec = dec_spx::INSTRUCTION_SPECS[decoding_context->bytes[0]];

        return DecodeInstruction(&instruction_spec, decoding_context, cpu_state, memory);
    }
}
