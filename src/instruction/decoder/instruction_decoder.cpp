void DecodeByteFields(FieldSpec *byte_field_specs,
                      uint8_t byte_idx,
                      InstructionInput *instruction_input,
                      DecodingContext *decoding_context)
{
    for (uint8_t i = 0; i < BYTE_FIELDS_MAX_LEN; ++i)
    {
        FieldSpec field_spec = byte_field_specs[i];

        if (field_spec.type == FieldSpecType_None)
        {
            break;
        }

        switch (field_spec.type)
        {
            case FieldSpecType_None:
            {

            } break;
            case FieldSpecType_D:
            {
                decoding_context->d = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
            case FieldSpecType_S:
            {
                decoding_context->s = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
            case FieldSpecType_V:
            {
                decoding_context->v = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
            case FieldSpecType_W:
            {
                decoding_context->w = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
            case FieldSpecType_MOD:
            {
                decoding_context->mod = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
            case FieldSpecType_RM:
            {
                decoding_context->r_m = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
            case FieldSpecType_REG:
            {
                decoding_context->reg = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
            case FieldSpecType_SR:
            {
                decoding_context->sr = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
            case FieldSpecType_DISP_8:
            {
                decoding_context->displacement = DecodeDisplacement8Bit(instruction_input, decoding_context);
            } break;
            case FieldSpecType_DISP:
            {
                decoding_context->displacement = DecodeDisplacement(instruction_input, decoding_context);
            } break;
            case FieldSpecType_DATA_8:
            {
                decoding_context->data = DecodeByte(instruction_input, decoding_context);
            } break;
            case FieldSpecType_DATA_LO:
            {
                decoding_context->data = DecodeByte(instruction_input, decoding_context);
            } break;
            case FieldSpecType_DATA_HI:
            {
                decoding_context->data = DecodeDataHighByte(instruction_input, decoding_context);
            } break;
            case FieldSpecType_ADDR_LO:
            {
                decoding_context->addr = DecodeByte(instruction_input, decoding_context);
            } break;
            case FieldSpecType_ADDR_HI:
            {
                decoding_context->addr = DecodeAddrHighByte(instruction_input, decoding_context);
            } break;
            case FieldSpecType_OpcodeExtension:
            {
                decoding_context->opcode_extension = DecodeField(field_spec, byte_idx, instruction_input, decoding_context);
            } break;
        }
    }
}

void DecodeOperands(Instruction *instruction,
                    InstructionFormatSpec *instruction_format,
                    DecodingContext *decoding_context)
{
    size_t num_operands = ARRAY_SIZE(instruction_format->operand_types);

    if (num_operands == 2 &&
        instruction_format->operand_types[0] == OperandSpecType_RegisterOrMemoryAddress &&
        instruction_format->operand_types[1] == OperandSpecType_RegisterOrMemoryAddress)
    {
        if (decoding_context->d == 0)
        {
            DecodeOperandRegisterOrMemoryAddress(&instruction->operands[0], decoding_context);
            DecodeOperandRegister(&instruction->operands[1], decoding_context);
        }
        else
        {
            DecodeOperandRegister(&instruction->operands[0], decoding_context);
            DecodeOperandRegisterOrMemoryAddress(&instruction->operands[1], decoding_context);
        }
        return;
    }

    for (uint8_t i = 0; i < num_operands; ++i)
    {
        OperandSpecType operand_type_spec = instruction_format->operand_types[i];

        if (operand_type_spec == OperandSpecType_None)
        {
            break;
        }

        switch (operand_type_spec)
        {
            case OperandSpecType_None:
            {

            } break;
            case OperandSpecType_Register:
            {
                DecodeOperandRegister(&instruction->operands[i], decoding_context);
            } break;
            case OperandSpecType_SegmentRegister:
            {
                DecodeOperandSegmentRegister(&instruction->operands[i], decoding_context);
            } break;
            case OperandSpecType_DataRegister:
            {
                DecodeOperandDataRegister(&instruction->operands[i], decoding_context);
            } break;
            case OperandSpecType_RegisterOrMemoryAddress:
            {
                DecodeOperandRegisterOrMemoryAddress(&instruction->operands[i], decoding_context);
            } break;
            case OperandSpecType_DirectMemoryAddress:
            {
                DecodeOperandDirectAddress(&instruction->operands[i], decoding_context);
            } break;
            case OperandSpecType_Accumulator:
            {
                DecodeOperandAccumulator(&instruction->operands[i], decoding_context);
            } break;
            case OperandSpecType_Immediate:
            {
                DecodeOperandImmediate(&instruction->operands[i], decoding_context);
            } break;
            case OperandSpecType_LabelLikeDisplacement:
            {
                DecodeOperandLabelLikeDisplacement(&instruction->operands[i], decoding_context);
            } break;
            case OperandSpecType_ShiftRotateCount:
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
    InstructionSpecBody *instruction_spec_body = 0;

    switch (instruction_spec->type)
    {
        case InstructionSpecType_None:
        {
            return instruction;
        } break;
        case InstructionSpecType_Regular:
        {
            instruction_spec_body = &instruction_spec->bodies[0];
            DecodeByteFields(instruction_spec_body->byte_1, 0, instruction_input, decoding_context);
            DecodeByteFields(instruction_spec_body->byte_2, 1, instruction_input, decoding_context);
            DecodeByteFields(instruction_spec_body->byte_3456, 2, instruction_input, decoding_context);
        } break;
        case InstructionSpecType_ExtendedOpcode:
        {
            DecodeByteFields(OPCODE_EXT_BYTE_FIELDS, 1, instruction_input, decoding_context);

            instruction_spec_body = &instruction_spec->bodies[decoding_context->opcode_extension];
            DecodeByteFields(instruction_spec_body->byte_1, 0, instruction_input, decoding_context);
            DecodeByteFields(instruction_spec_body->byte_3456, 2, instruction_input, decoding_context);
        } break;
    }

    DecodeOperands(&instruction, &instruction_spec_body->format, decoding_context);
    instruction.mnemonic = instruction_spec_body->format.mnemonic;

    return instruction;
}

Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    InstructionSpec instruction_spec = INSTRUCTION_SPECS[decoding_context->bytes[0]];

    return DecodeInstruction(&instruction_spec, instruction_input, decoding_context);
}
