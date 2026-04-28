namespace cpu::instruction_decoding::core
{
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::instruction::Instruction;
    using cpu::instruction_decoding::context::DecodingContext;
    using cpu::instruction_decoding::fields::DecodeByteFields;
    using cpu::instruction_decoding::operands::DecodeOperands;
    using cpu::instruction_decoding::specs::InstructionSpec;
    using cpu::instruction_decoding::specs::InstructionSpecBody;
    using cpu::instruction_decoding::specs::InstructionSpecType;
    using cpu::instruction_decoding::specs::OPCODE_EXT_BYTE_FIELDS;
    using cpu::instruction_decoding::specs::INSTRUCTION_SPECS;

    Instruction DecodeInstruction(InstructionSpec *instruction_spec,
                                  DecodingContext *decoding_context,
                                  CpuState *cpu_state,
                                  Memory *memory)
    {
        Instruction instruction = {};
        InstructionSpecBody *instruction_spec_body = 0;

        switch (instruction_spec->type)
        {
            case InstructionSpecType::None:
            {
                return instruction;
            } break;
            case InstructionSpecType::Regular:
            {
                instruction_spec_body = &instruction_spec->bodies[0];
                DecodeByteFields(instruction_spec_body->byte_1, 0, decoding_context, cpu_state, memory);
                DecodeByteFields(instruction_spec_body->byte_2, 1, decoding_context, cpu_state, memory);
                DecodeByteFields(instruction_spec_body->byte_3456, 2, decoding_context, cpu_state, memory);
            } break;
            case InstructionSpecType::ExtendedOpcode:
            {
                DecodeByteFields(OPCODE_EXT_BYTE_FIELDS, 1, decoding_context, cpu_state, memory);

                instruction_spec_body = &instruction_spec->bodies[decoding_context->opcode_extension];
                DecodeByteFields(instruction_spec_body->byte_1, 0, decoding_context, cpu_state, memory);
                DecodeByteFields(instruction_spec_body->byte_3456, 2, decoding_context, cpu_state, memory);
            } break;
        }

        DecodeOperands(&instruction,
                       instruction_spec_body->format.operand_types,
                       ARRAY_SIZE(instruction_spec_body->format.operand_types),
                       decoding_context);
        instruction.mnemonic = instruction_spec_body->format.mnemonic;
        instruction.is_wide = decoding_context->w;

        return instruction;
    }

    Instruction DecodeInstruction(DecodingContext *decoding_context, CpuState *cpu_state, Memory *memory)
    {
        InstructionSpec instruction_spec = INSTRUCTION_SPECS[decoding_context->bytes[0]];

        return DecodeInstruction(&instruction_spec, decoding_context, cpu_state, memory);
    }
}
