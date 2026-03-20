namespace cpu::state
{
    CpuState::CpuState()
    {
        static_assert(
            RegisterId_Count == ARRAY_SIZE(REGISTERS), "Number of register id enums and registers must be equal");

        memcpy(this->registers, REGISTERS, sizeof(REGISTERS));
    }

    uint16_t GetRegisterValue(Register *registers, RegisterId register_id)
    {
        Register *register_ = &registers[register_id];
        switch (register_->slice)
        {
            case RegisterSlice_None:
            {
            } break;
            case RegisterSlice_Low:
            case RegisterSlice_High:
            {
                return register_->byte_value;
            } break;
            case RegisterSlice_Both:
            {
                uint8_t high_byte_value = registers[register_->halves.high_half_id].byte_value;
                uint8_t low_byte_value = registers[register_->halves.low_half_id].byte_value;

                return ((uint16_t) high_byte_value << 8) | low_byte_value;
            } break;
            case RegisterSlice_Full:
            {
                return register_->full_value;
            } break;
        }

        return 0;
    }

    void SetRegisterValue(Register *registers, RegisterId register_id, uint16_t value)
    {
        Register *register_ = &registers[register_id];
        switch (register_->slice)
        {
            case RegisterSlice_None:
            {
            } break;
            case RegisterSlice_Low:
            case RegisterSlice_High:
            {
                register_->byte_value = value;
            } break;
            case RegisterSlice_Both:
            {
                registers[register_->halves.low_half_id].byte_value = value;
                registers[register_->halves.high_half_id].byte_value = value >> 8;
            } break;
            case RegisterSlice_Full:
            {
                register_->full_value = value;
            } break;
        }
    }
}
