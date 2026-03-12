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

    uint16_t GetValue() const;
    void SetValue(uint16_t value);
};