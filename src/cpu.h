#ifndef CPU_H
#define CPU_H

namespace cpu
{
    enum Register8BitId : U8
    {
        Register8BitId_None,

        Register8BitId_AL,
        Register8BitId_AH,
        Register8BitId_BL,
        Register8BitId_BH,
        Register8BitId_CL,
        Register8BitId_CH,
        Register8BitId_DL,
        Register8BitId_DH,

        Register8BitId_Count
    };

    enum Register16BitId : U8
    {
        Register16BitId_None,

        Register16BitId_AX,
        Register16BitId_BX,
        Register16BitId_CX,
        Register16BitId_DX,
        Register16BitId_SP,
        Register16BitId_BP,
        Register16BitId_SI,
        Register16BitId_DI,

        Register16BitId_ES,
        Register16BitId_CS,
        Register16BitId_SS,
        Register16BitId_DS,

        Register16BitId_IP,

        Register16BitId_Count
    };

    typedef U16 Flags;
    enum FlagId : U16
    {
        FlagId_SF = (1 << 0),
        FlagId_ZF = (1 << 1),

        FlagId_Count
    };

    struct CpuState
    {
        Flags flags;  // NOTE: technically, this is *also* a register
        U16 registers[Register16BitId_Count] = {};
    };

    U16 GetRegisterValue(CpuState* cpu_state,
                         Register8BitId register_8_bit_id);

    void SetRegisterValue(CpuState* cpu_state,
                          Register8BitId register_8_bit_id,
                          U8 value);

    U16 GetRegisterValue(CpuState* cpu_state,
                         Register16BitId register_16_bit_id);

    void SetRegisterValue(CpuState* cpu_state,
                          Register16BitId register_16_bit_id,
                          U16 value);

    void IncrementIP(CpuState* cpu_state,
                     I32 increment);

    void IncrementSP(CpuState* cpu_state);

    void DecrementSP(CpuState* cpu_state);
}

#endif // CPU_H
