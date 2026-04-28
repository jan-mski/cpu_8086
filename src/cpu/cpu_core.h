#ifndef CPU_CORE_H
#define CPU_CORE_H

namespace cpu::core
{
    enum class Register8BitId : uint8_t
    {
        None,

        AL,
        AH,
        BL,
        BH,
        CL,
        CH,
        DL,
        DH,

        Count
    };

    enum class Register16BitId : uint8_t
    {
        None,

        AX,
        BX,
        CX,
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
        bool GetFlagValue(FlagId flag_id);

        void SetFlagValue(FlagId flag_id, bool value);

        uint16_t GetRegisterValue(Register8BitId register_8_bit_id);

        void SetRegisterValue(Register8BitId register_8_bit_id, uint8_t value);

        uint16_t GetRegisterValue(Register16BitId register_16_bit_id);

        void SetRegisterValue(Register16BitId register_16_bit_id, uint16_t value);

        void IncrementIP(int32_t increment);

        void IncrementSP();

        void DecrementSP();

    private:
        bool flags[std::to_underlying(FlagId::Count)] = {};
        uint16_t registers[std::to_underlying(Register16BitId::Count)] = {};
    };
}

#endif // CPU_CORE_H
