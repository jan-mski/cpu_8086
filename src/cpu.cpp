namespace cpu
{
    U16 GetRegisterValue(CpuState* cpu_state,
                         Register8BitId register_8_bit_id)
    {
        U8* registers_8_bit = (U8*) cpu_state->registers;

        return registers_8_bit[register_8_bit_id + 1];
    }

    void SetRegisterValue(CpuState* cpu_state,
                          Register8BitId register_8_bit_id,
                          U8 value)
    {
        U8* registers_8_bit = (U8*) cpu_state->registers;
        registers_8_bit[register_8_bit_id + 1] = value;
    }

    U16 GetRegisterValue(CpuState* cpu_state,
                         Register16BitId register_16_bit_id)
    {
        return cpu_state->registers[register_16_bit_id];
    }

    void SetRegisterValue(CpuState* cpu_state,
                          Register16BitId register_16_bit_id,
                          U16 value)
    {
        cpu_state->registers[register_16_bit_id] = value;
    }

    void IncrementIP(CpuState* cpu_state,
                     I32 increment)
    {
        cpu_state->registers[Register16BitId_IP] += increment;
    }

    void IncrementSP(CpuState* cpu_state)
    {
        cpu_state->registers[Register16BitId_SP] += 2;
    }

    void DecrementSP(CpuState* cpu_state)
    {
        cpu_state->registers[Register16BitId_SP] -= 2;
    }
}
