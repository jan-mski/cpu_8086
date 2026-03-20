namespace cpu::state
{
    enum RegisterId : uint8_t
    {
        RegisterId_None,

        RegisterId_AL,
        RegisterId_AH,
        RegisterId_AX,
        RegisterId_BL,
        RegisterId_BH,
        RegisterId_BX,
        RegisterId_CL,
        RegisterId_CH,
        RegisterId_CX,
        RegisterId_DL,
        RegisterId_DH,
        RegisterId_DX,
        RegisterId_SP,
        RegisterId_BP,
        RegisterId_SI,
        RegisterId_DI,

        RegisterId_ES,
        RegisterId_CS,
        RegisterId_SS,
        RegisterId_DS,

        RegisterId_Count
    };

    enum RegisterSlice : uint8_t
    {
        RegisterSlice_None,

        RegisterSlice_Low,
        RegisterSlice_High,
        RegisterSlice_Both,
        RegisterSlice_Full
    };

    struct RegisterHalves
    {
        RegisterId low_half_id;
        RegisterId high_half_id;
    };

    struct Register
    {
        RegisterId id;

        RegisterSlice slice;

        union
        {
            uint8_t byte_value;
            RegisterHalves halves;
            uint16_t full_value;
        };
    };

    static const Register REGISTERS[RegisterId_Count] = {
        {},

        {.id = RegisterId_AL, .slice = RegisterSlice_Low},
        {.id = RegisterId_AH, .slice = RegisterSlice_High},
        {.id = RegisterId_AX, .slice = RegisterSlice_Both, .halves{RegisterId_AL, RegisterId_AH}},
        {.id = RegisterId_BL, .slice = RegisterSlice_Low},
        {.id = RegisterId_BH, .slice = RegisterSlice_High},
        {.id = RegisterId_BX, .slice = RegisterSlice_Both, .halves{RegisterId_BL, RegisterId_BH}},
        {.id = RegisterId_CL, .slice = RegisterSlice_Low},
        {.id = RegisterId_CH, .slice = RegisterSlice_High},
        {.id = RegisterId_CX, .slice = RegisterSlice_Both, .halves{RegisterId_CL, RegisterId_CH}},
        {.id = RegisterId_DL, .slice = RegisterSlice_Low},
        {.id = RegisterId_DH, .slice = RegisterSlice_High},
        {.id = RegisterId_DX, .slice = RegisterSlice_Both, .halves{RegisterId_DL, RegisterId_DH}},
        {.id = RegisterId_SP, .slice = RegisterSlice_Full},
        {.id = RegisterId_BP, .slice = RegisterSlice_Full},
        {.id = RegisterId_SI, .slice = RegisterSlice_Full},
        {.id = RegisterId_DI, .slice = RegisterSlice_Full},

        {.id = RegisterId_ES, .slice = RegisterSlice_Full},
        {.id = RegisterId_CS, .slice = RegisterSlice_Full},
        {.id = RegisterId_SS, .slice = RegisterSlice_Full},
        {.id = RegisterId_DS, .slice = RegisterSlice_Full}
    };

    enum FlagId : uint8_t
    {
        FlagId_None,

        FlagId_TF_NotImplemented,
        FlagId_DF_NotImplemented,
        FlagId_IF_NotImplemented,
        FlagId_OF_NotImplemented,
        FlagId_SF,
        FlagId_ZF,
        FlagId_AF_NotImplemented,
        FlagId_PF_NotImplemented,
        FlagId_CF_NotImplemented,

        FlagId_Count
    };

    struct CpuState
    {
        Register registers[RegisterId_Count];
        bool flags[FlagId_Count] = {};

        CpuState();
    };

    uint16_t GetRegisterValue(Register *registers, RegisterId register_id);

    void SetRegisterValue(Register *registers, RegisterId register_id, uint16_t value);
}
