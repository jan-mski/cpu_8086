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
Register SEGMENT_REGISTERS[] = {
    REGISTER_ES,
    REGISTER_CS,
    REGISTER_SS,
    REGISTER_DS
};

void SetEffectiveAddressRegisters(Operand *operand, Register *effective_address_registers)
{
    for (uint8_t i = 0; i < ARRAY_SIZE(operand->memory_address.registers); ++i)
    {
        operand->memory_address.registers[i] = effective_address_registers[i];
    }
}

void SetEffectiveAddressNoDisplacement(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_MEMORY_ADDRESS;
    SetEffectiveAddressRegisters(operand, EFFECTIVE_ADDRESS_REGISTERS[decoding_context->r_m]);
}

void SetDirectAddressFromDisplacement(Operand *operand, DecodingContext *decoding_context)
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
                SetDirectAddressFromDisplacement(operand, decoding_context);
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

void DecodeOperandSegmentRegister(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_REGISTER;
    operand->register_ = SEGMENT_REGISTERS[decoding_context->sr];
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

void DecodeOperandAccumulator(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_REGISTER;
    operand->register_ = decoding_context->w == 0 ? REGISTER_AL : REGISTER_AX;
}

void DecodeOperandDirectAddress(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_MEMORY_ADDRESS;
    operand->memory_address.direct = true;
    operand->memory_address.displacement = decoding_context->addr;
}

void DecodeOperandLabelLikeDisplacement(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OPERAND_TYPE_LABEL_LIKE_DISPLACEMENT;
    operand->label_like_displacement = decoding_context->displacement;
}
