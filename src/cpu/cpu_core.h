#define ARRAY_SIZE(array) ((sizeof(array) / sizeof(array[0])))

namespace cpu::core
{
    enum class RegisterId : uint8_t
    {
        None,

        AL,
        AH,
        AX,
        BL,
        BH,
        BX,
        CL,
        CH,
        CX,
        DL,
        DH,
        DX,
        SP,
        BP,
        SI,
        DI,

        ES,
        CS,
        SS,
        DS,

        IP,

        Count
    };

    enum class RegisterSlice : uint8_t
    {
        None,

        Low,
        High,
        Both,
        Full
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

    static const Register REGISTERS[std::to_underlying(RegisterId::Count)] = {
        {},

        { .id = RegisterId::AL, .slice = RegisterSlice::Low },
        { .id = RegisterId::AH, .slice = RegisterSlice::High },
        { .id = RegisterId::AX, .slice = RegisterSlice::Both, .halves { RegisterId::AL, RegisterId::AH } },
        { .id = RegisterId::BL, .slice = RegisterSlice::Low },
        { .id = RegisterId::BH, .slice = RegisterSlice::High },
        { .id = RegisterId::BX, .slice = RegisterSlice::Both, .halves { RegisterId::BL, RegisterId::BH } },
        { .id = RegisterId::CL, .slice = RegisterSlice::Low },
        { .id = RegisterId::CH, .slice = RegisterSlice::High },
        { .id = RegisterId::CX, .slice = RegisterSlice::Both, .halves { RegisterId::CL, RegisterId::CH } },
        { .id = RegisterId::DL, .slice = RegisterSlice::Low },
        { .id = RegisterId::DH, .slice = RegisterSlice::High },
        { .id = RegisterId::DX, .slice = RegisterSlice::Both, .halves { RegisterId::DL, RegisterId::DH } },
        { .id = RegisterId::SP, .slice = RegisterSlice::Full },
        { .id = RegisterId::BP, .slice = RegisterSlice::Full },
        { .id = RegisterId::SI, .slice = RegisterSlice::Full },
        { .id = RegisterId::DI, .slice = RegisterSlice::Full },

        { .id = RegisterId::ES, .slice = RegisterSlice::Full },
        { .id = RegisterId::CS, .slice = RegisterSlice::Full },
        { .id = RegisterId::SS, .slice = RegisterSlice::Full },
        { .id = RegisterId::DS, .slice = RegisterSlice::Full },

        { .id = RegisterId::IP, .slice = RegisterSlice::Full }
    };

    enum class FlagId : uint8_t
    {
        None,

        TF_NotImplemented,
        DF_NotImplemented,
        IF_NotImplemented,
        OF_NotImplemented,
        SF,
        ZF,
        AF_NotImplemented,
        PF_NotImplemented,
        CF_NotImplemented,

        Count,
    };

    struct Cpu
    {
        Register registers[std::to_underlying(RegisterId::Count)];
        bool flags[std::to_underlying(FlagId::Count)] = {};

        Cpu();
    };

    uint16_t GetRegisterValue(Register *registers, RegisterId register_id);

    void SetRegisterValue(Register *registers, RegisterId register_id, uint16_t value);
}
