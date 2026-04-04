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

    CpuState::CpuState() : registers {
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
    }
    {
        static_assert(
            (to_underlying(RegisterId::Count)) == ARRAY_SIZE(registers),
            "Number of register id enums and registers must be equal");
    }

    uint16_t CpuState::GetRegisterValue(RegisterId register_id)
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

    void CpuState::SetRegisterValue(RegisterId register_id, uint16_t value)
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

    void CpuState::IncrementInstructionPointer(int32_t increment)
    {
        SetRegisterValue(RegisterId::IP, GetRegisterValue(RegisterId::IP) + increment);
    }
}
