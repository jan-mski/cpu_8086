Register registers[] = {
    {},

    { .id = RegisterId_AL, .slice = RegisterSlice_Low },
    { .id = RegisterId_AH, .slice = RegisterSlice_High },
    { .id = RegisterId_AX, .slice = RegisterSlice_Both, .halves { RegisterId_AL, RegisterId_AH } },
    { .id = RegisterId_BL, .slice = RegisterSlice_Low },
    { .id = RegisterId_BH, .slice = RegisterSlice_High },
    { .id = RegisterId_BX, .slice = RegisterSlice_Both, .halves { RegisterId_BL, RegisterId_BH } },
    { .id = RegisterId_CL, .slice = RegisterSlice_Low },
    { .id = RegisterId_CH, .slice = RegisterSlice_High },
    { .id = RegisterId_CX, .slice = RegisterSlice_Both, .halves { RegisterId_CL, RegisterId_CH } },
    { .id = RegisterId_DL, .slice = RegisterSlice_Low },
    { .id = RegisterId_DH, .slice = RegisterSlice_High },
    { .id = RegisterId_DX, .slice = RegisterSlice_Both, .halves { RegisterId_DL, RegisterId_DH } },
    { .id = RegisterId_SP, .slice = RegisterSlice_Full },
    { .id = RegisterId_BP, .slice = RegisterSlice_Full },
    { .id = RegisterId_SI, .slice = RegisterSlice_Full },
    { .id = RegisterId_DI, .slice = RegisterSlice_Full },

    { .id = RegisterId_ES, .slice = RegisterSlice_Full },
    { .id = RegisterId_CS, .slice = RegisterSlice_Full },
    { .id = RegisterId_SS, .slice = RegisterSlice_Full },
    { .id = RegisterId_DS, .slice = RegisterSlice_Full }
};

uint16_t Register::GetValue() const
{
    static_assert(RegisterId_Count == ARRAY_SIZE(registers), "Number of register id enums and registers must be equal");

    switch (slice)
    {
        case RegisterSlice_None:
        {

        } break;
        case RegisterSlice_Low:
        case RegisterSlice_High:
        {
            return byte_value;
        } break;
        case RegisterSlice_Both:
        {
            uint8_t high_byte_value = registers[halves.high_half_id].byte_value;
            uint8_t low_byte_value = registers[halves.low_half_id].byte_value;

            return ((uint16_t) high_byte_value) << 8 | low_byte_value;
        } break;
        case RegisterSlice_Full:
        {
            return full_value;
        }
    }

    return 0;
}

void Register::SetValue(uint16_t value)
{
    switch (slice)
    {
        case RegisterSlice_None:
        {

        } break;
        case RegisterSlice_Low:
        case RegisterSlice_High:
        {
            byte_value = value;
        } break;
        case RegisterSlice_Both:
        {
            registers[halves.low_half_id].byte_value = value;
            registers[halves.high_half_id].byte_value = value >> 8;
        } break;
        case RegisterSlice_Full:
        {
            full_value = value;
        } break;
    }
}
