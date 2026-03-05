void SetDirectAddressFromDisplacement(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_MemoryAddress;
    operand->memory_address.direct = true;
    operand->memory_address.displacement = decoding_context->displacement;
}

void SetEffectiveAddress(Operand *operand, DecodingContext *decoding_context)
{
    Register effective_address_registers[][2] = {
        {Register_BX, Register_SI},
        {Register_BX, Register_DI},
        {Register_BP, Register_SI},
        {Register_BP, Register_DI},
        {Register_SI},
        {Register_DI},
        {Register_BP},
        {Register_BX}
    };

    operand->type = OperandType_MemoryAddress;
    for (uint8_t i = 0; i < ARRAY_SIZE(operand->memory_address.registers); ++i)
    {
        operand->memory_address.registers[i] = effective_address_registers[decoding_context->r_m][i];
    }
    operand->memory_address.displacement = decoding_context->displacement;
}

void SetRegister(Operand *operand, uint8_t w, uint8_t reg_or_r_m)
{
    Register registers_by_w[][8] = {
        {Register_AL, Register_CL, Register_DL, Register_BL, Register_AH, Register_CH, Register_DH, Register_BH},
        {Register_AX, Register_CX, Register_DX, Register_BX, Register_SP, Register_BP, Register_SI, Register_DI}
    };

    operand->type = OperandType_Register;
    operand->register_ = registers_by_w[w][reg_or_r_m];
}

void DecodeOperandRegisterOrMemoryAddress(Operand *operand, DecodingContext *decoding_context)
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
                SetEffectiveAddress(operand, decoding_context);
            }
        } break;
        case 0b01:
        case 0b10:
        {
            SetEffectiveAddress(operand, decoding_context);
        } break;
        default:
        {
            SetRegister(operand, decoding_context->w, decoding_context->r_m);
            return;
        } break;
    }

    MemoryAddressQualifier qualifier = decoding_context->w == 1
                                           ? MemoryAddressQualifier_Word
                                           : MemoryAddressQualifier_Byte;
    operand->memory_address.qualifier = qualifier;
}

void DecodeOperandRegister(Operand *operand, DecodingContext *decoding_context)
{
    SetRegister(operand, decoding_context->w, decoding_context->reg);
}

void DecodeOperandSegmentRegister(Operand *operand, DecodingContext *decoding_context)
{
    Register segment_registers[] = {Register_ES, Register_CS, Register_SS, Register_DS};

    operand->type = OperandType_Register;
    operand->register_ = segment_registers[decoding_context->sr];
}

void DecodeOperandImmediate(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_Immediate;
    operand->immediate_value = decoding_context->data;
}

void DecodeOperandAccumulator(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_Register;
    operand->register_ = decoding_context->w == 1
                             ? Register_AX
                             : Register_AL;
}

void DecodeOperandDataRegister(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_Register;
    operand->register_ = Register_DX;
}

void DecodeOperandDirectAddress(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_MemoryAddress;
    operand->memory_address.direct = true;
    operand->memory_address.displacement = decoding_context->addr;
}

void DecodeOperandLabelLikeDisplacement(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_LabelLikeDisplacement;
    operand->label_like_displacement = decoding_context->displacement;
}

void DecodeOperandShiftRotateCount(Operand *operand, DecodingContext *decoding_context)
{
    if (decoding_context->v == 0)
    {
        operand->type = OperandType_Immediate;
        operand->immediate_value = 1;
    } else
    {
        operand->type = OperandType_Register;
        operand->register_ = Register_CL;
    }
}
