void DecodeByteFields(FieldSpec *byte_field_specs,
                      uint8_t byte_index,
                      InstructionInput *instruction_input,
                      DecodingContext *decoding_context)
{
    for (uint8_t i = 0; i < BYTE_FIELDS_MAX_LEN; ++i)
    {
        FieldSpec field_spec = byte_field_specs[i];

        if (field_spec.type == FIELD_TYPE_SPEC_NONE)
        {
            break;
        }

        switch (field_spec.type)
        {
            case FIELD_TYPE_SPEC_NONE:
            {

            } break;
            case FIELD_TYPE_SPEC_D:
            {
                DecodeD(field_spec, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_S:
            {
                DecodeS(field_spec, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_V:
            {
                DecodeV(field_spec, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_W:
            {
                DecodeW(field_spec, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_MOD:
            {
                DecodeMod(instruction_input, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_RM:
            {
                DecodeRM(instruction_input, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_REG:
            {
                DecodeReg(instruction_input, byte_index, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_SR:
            {
                DecodeSR(instruction_input, byte_index, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DISP_8:
            {
                DecodeDisplacement8Bit(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DISP:
            {
                DecodeDisplacement(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DATA_8:
            {
                DecodeDataLowByte(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DATA_LO:
            {
                DecodeDataLowByte(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DATA_HI:
            {
                DecodeDataHighByte(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_ADDR_LO:
            {
                DecodeAddrLowByte(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_ADDR_HI:
            {
                DecodeAddrHighByte(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_OPCODE_EXTENSION:
            {
                DecodeOpcodeExtension(instruction_input, decoding_context);
            } break;
        }
    }
}

void DecodeOperands(Instruction *instruction,
                    InstructionFormatSpec *instruction_format,
                    DecodingContext *decoding_context)
{
    if ((instruction_format->operand_types[0] == OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS &&
         instruction_format->operand_types[1] == OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS))
    {
        DecodeOperandsRegisterOrMemoryAndEither(instruction, decoding_context);
        return;
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(instruction_format->operand_types); ++i)
    {
        OperandTypeSpec operand_type_spec = instruction_format->operand_types[i];

        if (operand_type_spec == OPERAND_TYPE_SPEC_NONE)
        {
            break;
        }

        switch (operand_type_spec)
        {
            case OPERAND_TYPE_SPEC_NONE:
            {

            } break;
            case OPERAND_TYPE_SPEC_REGISTER:
            {
                DecodeOperandRegister(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_SEGMENT_REGISTER:
            {
                DecodeOperandSegmentRegister(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_DATA_REGISTER:
            {
                DecodeOperandDataRegister(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS:
            {
                DecodeOperandRegisterOrMemoryAddress(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_DIRECT_MEMORY_ADDRESS:
            {
                DecodeOperandDirectAddress(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_ACCUMULATOR:
            {
                DecodeOperandAccumulator(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_IMMEDIATE:
            {
                DecodeOperandImmediate(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_LABEL_LIKE_DISPLACEMENT:
            {
                DecodeOperandLabelLikeDisplacement(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_SHIFT_ROTATE_COUNT:
            {
                DecodeOperandShiftRotateCount(&instruction->operands[i], decoding_context);
            } break;
        }
    }
}

Instruction DecodeInstruction(InstructionSpec *instruction_spec,
                              InstructionInput *instruction_input,
                              DecodingContext *decoding_context)
{
    Instruction instruction = {};
    Instruction *instruction_ptr = &instruction;
    InstructionSpecBody *instruction_spec_body = 0;

    switch (instruction_spec->type)
    {
        case INSTRUCTION_TYPE_NONE:
        {
            return instruction;
        } break;
        case INSTRUCTION_TYPE_REGULAR:
        {
            instruction_spec_body = &instruction_spec->bodies[0];
            DecodeByteFields(instruction_spec_body->byte_1, 0, instruction_input, decoding_context);
            DecodeByteFields(instruction_spec_body->byte_2, 1, instruction_input, decoding_context);
            DecodeByteFields(instruction_spec_body->byte_3456, decoding_context->num_bytes_read, instruction_input,
                    decoding_context);
        } break;
        case INSTRUCTION_TYPE_EXTENDED_OPCODE:
        {
            FieldSpec byte_field_specs[BYTE_FIELDS_MAX_LEN] = OPCODE_EXT_BYTE_FIELDS;
            ReadNextBytesToIndex(instruction_input, decoding_context, OPCODE_EXT_BYTE_INDEX);
            DecodeByteFields(byte_field_specs, OPCODE_EXT_BYTE_INDEX, instruction_input, decoding_context);

            instruction_spec_body = &instruction_spec->bodies[decoding_context->opcode_extension];
            DecodeByteFields(instruction_spec_body->byte_1, 0, instruction_input, decoding_context);
            DecodeByteFields(instruction_spec_body->byte_3456, decoding_context->num_bytes_read, instruction_input,
                    decoding_context);

        } break;
    }

    DecodeOperands(instruction_ptr, &instruction_spec_body->format, decoding_context);
    instruction.mnemonic = instruction_spec_body->format.mnemonic;

    return instruction;
}

Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    InstructionSpec instruction_spec = INSTRUCTION_SPECS[decoding_context->bytes[0]];

    return DecodeInstruction(&instruction_spec, instruction_input, decoding_context);
}
