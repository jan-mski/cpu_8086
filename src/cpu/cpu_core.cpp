namespace cpu::core
{
    using std::to_underlying;
    using memory::Memory;
    using cpu::instruction::Instruction;
    using cpu::instruction::Mnemonic;
    using cpu::instruction_decoding::core::DecodeInstruction;
    using cpu::instruction_decoding::context::DecodingContext;
    using cpu::instruction_decoding::context::ReadNextInstructionByte;
    using cpu::instruction_execution::ExecuteInstruction;
    using text_output::PrintAsmString;
    using text_output::PrintExecutionTrace;
    using text_output::PrintFinalCpuState;

    Cpu::Cpu()
    {
        static_assert(
            (to_underlying(RegisterId::Count)) == ARRAY_SIZE(REGISTERS),
            "Number of register id enums and registers must be equal");

        memcpy(this->registers, REGISTERS, sizeof(REGISTERS));
    }

    uint16_t GetRegisterValue(Register *registers, RegisterId register_id)
    {
        Register *register_ = &registers[to_underlying(register_id)];
        switch (register_->slice)
        {
            case RegisterSlice::None:
            {
            } break;
            case RegisterSlice::Low:
            case RegisterSlice::High:
            {
                return register_->byte_value;
            } break;
            case RegisterSlice::Both:
            {
                uint8_t high_byte_value = registers[to_underlying(register_->halves.high_half_id)].byte_value;
                uint8_t low_byte_value = registers[to_underlying(register_->halves.low_half_id)].byte_value;

                return ((uint16_t) high_byte_value << 8) | low_byte_value;
            } break;
            case RegisterSlice::Full:
            {
                return register_->full_value;
            } break;
        }

        return 0;
    }

    void SetRegisterValue(Register *registers, RegisterId register_id, uint16_t value)
    {
        Register *register_ = &registers[to_underlying(register_id)];
        switch (register_->slice)
        {
            case RegisterSlice::None:
            {
            } break;
            case RegisterSlice::Low:
            case RegisterSlice::High:
            {
                register_->byte_value = value;
            } break;
            case RegisterSlice::Both:
            {
                registers[to_underlying(register_->halves.low_half_id)].byte_value = value;
                registers[to_underlying(register_->halves.high_half_id)].byte_value = value >> 8;
            } break;
            case RegisterSlice::Full:
            {
                register_->full_value = value;
            } break;
        }
    }
}
