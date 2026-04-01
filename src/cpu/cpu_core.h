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

    struct CpuState
    {
        Register registers[std::to_underlying(RegisterId::Count)];
        bool flags[std::to_underlying(FlagId::Count)] = {};

        CpuState();

        uint16_t GetRegisterValue(RegisterId register_id);

        void SetRegisterValue(RegisterId register_id, uint16_t value);

        void IncrementInstructionPointer(int32_t increment);
    };
}
