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

void SetEffectiveAddressNoDisplacement(Operand *operand, const InstructionDecodingContext *decoding_context)
{
    operand->type = OPERAND_MEMORY_ADDRESS;
    operand->memory_address.registers = EFFECTIVE_ADDRESS_REGISTERS[decoding_context->r_m];
}

void SetDirectAddress(Operand *operand, const InstructionDecodingContext *decoding_context)
{
    operand->type = OPERAND_MEMORY_ADDRESS;

    MemoryAddress *memory_address = &operand->memory_address;
    memory_address->direct = true;
    memory_address->displacement = decoding_context->displacement;
}

void SetEffectiveAddressWithDisplacement(Operand *operand, const InstructionDecodingContext *decoding_context)
{
    operand->type = OPERAND_MEMORY_ADDRESS;

    MemoryAddress *memory_address = &operand->memory_address;
    memory_address->registers = EFFECTIVE_ADDRESS_REGISTERS[decoding_context->r_m];
    memory_address->displacement = decoding_context->displacement;
}

void SetRegisterName(Operand *operand, const uint8_t w, const uint8_t reg_or_r_m)
{
    operand->type = OPERAND_REGISTER;
    operand->register_ = REGISTERS_BY_W[w][reg_or_r_m];
}

bool DecodeRegisterOrMemoryAddress(Operand *operand, const InstructionDecodingContext *decoding_context)
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
            return true;
        } break;
    }

    return false;
}

void DecodeRegister(Operand *operand, const InstructionDecodingContext *decoding_context)
{
    SetRegisterName(operand, decoding_context->w, decoding_context->reg);
}


void DecodeOperandsRegisterOrMemoryAndEither(InstructionDecodingContext *decoding_context)
{
    if (decoding_context->d == 0)
    {
        DecodeRegisterOrMemoryAddress(&decoding_context->operands[0], decoding_context);
        DecodeRegister(&decoding_context->operands[1], decoding_context);
    }
    else
    {
        DecodeRegister(&decoding_context->operands[0], decoding_context);
        DecodeRegisterOrMemoryAddress(&decoding_context->operands[1], decoding_context);
    }
}

void DecodeOperandsRegisterOrMemoryAndImmediate(InstructionDecodingContext *decoding_context)
{
    const bool is_register = DecodeRegisterOrMemoryAddress(&decoding_context->operands[0], decoding_context);

    Operand *right_operand = &decoding_context->operands[1];
    right_operand->type = OPERAND_IMMEDIATE;
    right_operand->immediate_value = decoding_context->data;

    if (!is_register)
    {
        const char *qualifier = decoding_context->w == 0 ? "byte" : "word";
        decoding_context->operands[0].memory_address.qualifier = qualifier;
    }
}

void DecodeOperandsRegisterAndImmediate(InstructionDecodingContext *decoding_context)
{
    DecodeRegister(&decoding_context->operands[0], decoding_context);

    Operand *right_operand = &decoding_context->operands[1];
    right_operand->type = OPERAND_IMMEDIATE;
    right_operand->immediate_value = decoding_context->data;
}

void DecodeOperandsAccumulatorAndMemory(InstructionDecodingContext *decoding_context)
{
    Operand *left_operand = &decoding_context->operands[0];
    left_operand->type = OPERAND_REGISTER;
    left_operand->register_ = REGISTER_AX;

    Operand *right_operand = &decoding_context->operands[1];
    right_operand->type = OPERAND_MEMORY_ADDRESS;
    right_operand->memory_address.direct = true;
    right_operand->memory_address.displacement = decoding_context->addr;
}

void DecodeOperandsMemoryAndAccumulator(InstructionDecodingContext *decoding_context)
{
    Operand *left_operand = &decoding_context->operands[0];
    left_operand->type = OPERAND_MEMORY_ADDRESS;
    left_operand->memory_address.direct = true;
    left_operand->memory_address.displacement = decoding_context->addr;

    Operand *right_operand = &decoding_context->operands[1];
    right_operand->type = OPERAND_REGISTER;
    right_operand->register_ = REGISTER_AX;
}

void DecodeOperandsAccumulatorAndImmediate(InstructionDecodingContext * decoding_context)
{
    Operand *left_operand = &decoding_context->operands[0];
    left_operand->type = OPERAND_REGISTER;
    left_operand->register_ = decoding_context->w == 0 ? REGISTER_AL : REGISTER_AX;

    Operand *right_operand = &decoding_context->operands[1];
    right_operand->type = OPERAND_IMMEDIATE;
    right_operand->immediate_value = decoding_context->data;
}

void DecodeOperandsReturnFromCall(InstructionDecodingContext *decoding_context)
{
    Operand *left_operand = &decoding_context->operands[0];
    left_operand->type = OPERAND_LABEL_LIKE_DISPLACEMENT;
    left_operand->label_like_displacement = decoding_context->displacement;
}
