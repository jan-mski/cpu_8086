void SetDirectAddressFromDisplacement(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_MemoryAddress;
    operand->memory_address.direct = true;
    operand->memory_address.displacement = decoding_context->displacement;
}

void SetEffectiveAddress(Operand *operand, DecodingContext *decoding_context)
{
    RegisterId effective_address_registers[][2] = {
        {RegisterId_BX, RegisterId_SI},
        {RegisterId_BX, RegisterId_DI},
        {RegisterId_BP, RegisterId_SI},
        {RegisterId_BP, RegisterId_DI},
        {RegisterId_SI},
        {RegisterId_DI},
        {RegisterId_BP},
        {RegisterId_BX}
    };

    operand->type = OperandType_MemoryAddress;
    for (uint8_t i = 0; i < ARRAY_SIZE(operand->memory_address.register_ids); ++i)
    {
        operand->memory_address.register_ids[i] = effective_address_registers[decoding_context->r_m][i];
    }
    operand->memory_address.displacement = decoding_context->displacement;
}

void SetRegister(Operand *operand, uint8_t w, uint8_t reg_or_r_m)
{
    RegisterId registers_by_w[][8] = {
        {RegisterId_AL, RegisterId_CL, RegisterId_DL, RegisterId_BL, RegisterId_AH, RegisterId_CH, RegisterId_DH, RegisterId_BH},
        {RegisterId_AX, RegisterId_CX, RegisterId_DX, RegisterId_BX, RegisterId_SP, RegisterId_BP, RegisterId_SI, RegisterId_DI}
    };

    operand->type = OperandType_Register;
    operand->register_id = registers_by_w[w][reg_or_r_m];
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
    RegisterId segment_registers[] = {RegisterId_ES, RegisterId_CS, RegisterId_SS, RegisterId_DS};

    operand->type = OperandType_Register;
    operand->register_id = segment_registers[decoding_context->sr];
}

void DecodeOperandImmediate(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_Immediate;
    operand->immediate_value = decoding_context->data;
}

void DecodeOperandAccumulator(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_Register;
    operand->register_id = decoding_context->w == 1
                             ? RegisterId_AX
                             : RegisterId_AL;
}

void DecodeOperandDataRegister(Operand *operand, DecodingContext *decoding_context)
{
    operand->type = OperandType_Register;
    operand->register_id = RegisterId_DX;
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
        operand->register_id = RegisterId_CL;
    }
}
