
Register REGISTERS_BY_W[][8] = {
    {
        REGISTER_AL,
        REGISTER_CL,
        REGISTER_DL,
        REGISTER_BL,
        REGISTER_AH,
        REGISTER_CH,
        REGISTER_DH,
        REGISTER_BH
    },
    {
        REGISTER_AX,
        REGISTER_CX,
        REGISTER_DX,
        REGISTER_BX,
        REGISTER_SP,
        REGISTER_BP,
        REGISTER_SI,
        REGISTER_DI
    }
};
Register EFFECTIVE_ADDRESS_REGISTERS[][2] = {
    {REGISTER_BX, REGISTER_SI},
    {REGISTER_BX, REGISTER_DI},
    {REGISTER_BP, REGISTER_SI},
    {REGISTER_BP, REGISTER_DI},
    {REGISTER_SI},
    {REGISTER_DI},
    {REGISTER_BP},
    {REGISTER_BX}
};

void SetEffectiveAddressRegisters(Operand *operand, Register *registers)
{
    for (uint8_t i = 0; i < REGISTERS_MAX_LEN; ++i)
    {
        operand->memory_address.registers[i] = registers[i];
    }
}

void SetEffectiveAddressNoDisplacement(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_MEMORY_ADDRESS;
    SetEffectiveAddressRegisters(operand, EFFECTIVE_ADDRESS_REGISTERS[decoding_context->r_m]);
}

void SetDirectAddress(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_MEMORY_ADDRESS;

    MemoryAddress *memory_address = &operand->memory_address;
    memory_address->direct = true;
    memory_address->displacement = decoding_context->displacement;
}

void SetEffectiveAddressWithDisplacement(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_MEMORY_ADDRESS;

    MemoryAddress *memory_address = &operand->memory_address;
    SetEffectiveAddressRegisters(operand, EFFECTIVE_ADDRESS_REGISTERS[decoding_context->r_m]);
    memory_address->displacement = decoding_context->displacement;
}

void SetRegisterName(Operand *operand, uint8_t w, uint8_t reg_or_r_m)
{
    operand->type = OPERAND_TYPE_REGISTER;
    operand->register_ = REGISTERS_BY_W[w][reg_or_r_m];
}

void DecodeOperandRegisterOrMemoryAddress(Operand *operand,
                                          DecodingContext *decoding_context,
                                          bool is_instruction_wide)
{
    switch (decoding_context->mod)
    {
        case 0b00:
        {
            if (decoding_context->r_m == 0b110)
            {
                SetDirectAddress(operand, decoding_context);
            } else
            {
                SetEffectiveAddressNoDisplacement(operand, decoding_context);
            }
        } break;
        case 0b01:
        case 0b10:
        {
            SetEffectiveAddressWithDisplacement(operand, decoding_context);
        } break;
        default:
        {
            SetRegisterName(operand, decoding_context->w, decoding_context->r_m);
            return;
        } break;
    }

    MemoryAddressQualifier qualifier = (is_instruction_wide || decoding_context->w == 1)
                                           ? MEMORY_ADDRESS_QUALIFIER_WORD
                                           : MEMORY_ADDRESS_QUALIFIER_BYTE;
    operand->memory_address.qualifier = qualifier;
}

void DecodeOperandRegister(Operand *operand, DecodingContext *decoding_context, bool is_instruction_wide)
{
    SetRegisterName(operand, (is_instruction_wide || decoding_context->w), decoding_context->reg);
}

void DecodeOperandsRegisterOrMemoryAndEither(Instruction *instruction, DecodingContext *decoding_context)
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
}

void DecodeOperandImmediate(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_IMMEDIATE;
    operand->immediate_value = decoding_context->data;
}

void DecodeOperandAccumulator(Operand *left_operand, DecodingContext *decoding_context)
{
    left_operand->type = OPERAND_TYPE_REGISTER;
    left_operand->register_ = decoding_context->w == 0 ? REGISTER_AL : REGISTER_AX;
    // left_operand->register_ = REGISTER_AX;
}

void DecodeOperandDirectAddress(Operand *right_operand, DecodingContext *decoding_context)
{
    right_operand->type = OPERAND_TYPE_MEMORY_ADDRESS;
    right_operand->memory_address.direct = true;
    right_operand->memory_address.displacement = decoding_context->addr;
}

void DecodeOperandLabelLikeDisplacement(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_LABEL_LIKE_DISPLACEMENT;
    operand->label_like_displacement = decoding_context->displacement;
}
