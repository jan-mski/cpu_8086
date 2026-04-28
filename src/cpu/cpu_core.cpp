namespace cpu::core
{
    using std::to_underlying;

    bool CpuState::GetFlagValue(FlagId flag_id)
    {
        return flags[std::to_underlying(flag_id)];
    }

    void CpuState::SetFlagValue(FlagId flag_id, bool value)
    {
        flags[std::to_underlying(flag_id)] = value;
    }

    uint16_t CpuState::GetRegisterValue(Register8BitId register_8_bit_id)
    {
        uint8_t *registers_8_bit = (uint8_t *) registers;  // assuming host is little endian for simplicity

        return registers_8_bit[to_underlying(register_8_bit_id) + 1];
    }

    void CpuState::SetRegisterValue(Register8BitId register_8_bit_id, uint8_t value)
    {
        uint8_t *registers_8_bit = (uint8_t *) registers;  // assuming host is little endian for simplicity
        registers_8_bit[to_underlying(register_8_bit_id) + 1] = value;
    }

    uint16_t CpuState::GetRegisterValue(Register16BitId register_16_bit_id)
    {
        return registers[to_underlying(register_16_bit_id)];
    }

    void CpuState::SetRegisterValue(Register16BitId register_16_bit_id, uint16_t value)
    {
        registers[to_underlying(register_16_bit_id)] = value;
    }

    void CpuState::IncrementIP(int32_t increment)
    {
        registers[to_underlying(Register16BitId::IP)] += increment;
    }

    void CpuState::IncrementSP()
    {
        registers[to_underlying(Register16BitId::SP)] += 2;
    }

    void CpuState::DecrementSP()
    {
        registers[to_underlying(Register16BitId::SP)] -= 2;
    }
}
