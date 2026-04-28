namespace cpu::instruction_execution::binary
{
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::instruction::Instruction;
    using cpu::instruction_execution::resolution::ResolvedOperand;
    using cpu::instruction_execution::resolution::ResolveOperand;

    uint16_t noop(ResolvedOperand _, ResolvedOperand b)
    {
        return b.GetValue();
    }

    uint16_t add(ResolvedOperand a, ResolvedOperand b)
    {
        return a.GetValue() + b.GetValue();
    }

    uint16_t subtract(ResolvedOperand a, ResolvedOperand b)
    {
        return a.GetValue() - b.GetValue();
    }

    uint16_t bitwise_and(ResolvedOperand a, ResolvedOperand b)
    {
        return a.GetValue() & b.GetValue();
    }

    uint16_t bitwise_or(ResolvedOperand a, ResolvedOperand b)
    {
        return a.GetValue() | b.GetValue();
    }

    uint16_t bitwise_xor(ResolvedOperand a, ResolvedOperand b)
    {
        return a.GetValue() ^ b.GetValue();
    }

    uint16_t bitwise_shl(ResolvedOperand a, ResolvedOperand b)
    {
        return a.GetValue() << b.GetValue();
    }

    uint16_t bitwise_shr(ResolvedOperand a, ResolvedOperand b)
    {
        return a.GetValue() >> b.GetValue();
    }

    uint16_t bitwise_sar(ResolvedOperand a, ResolvedOperand b)
    {
        uint16_t result = 0;
        uint16_t a_value = a.GetValue();
        uint16_t b_value = b.GetValue();

        if (a.is_instruction_wide)
        {
            int16_t a_signed = (int16_t) a_value;
            result = (uint16_t) (a_signed >> b_value);
        }
        else
        {
            int8_t a_signed = (int8_t) a_value;
            result = (uint8_t) (a_signed >> b_value);
        }

        return result;
    }
    
    uint16_t ExecuteBinaryInstruction(Instruction *instruction,
                                      CpuState *cpu_state,
                                      Memory *memory,
                                      bool do_set_result,
                                      BinaryOp op)
    {
        bool is_instruction_wide = instruction->is_wide;
        ResolvedOperand operand_1 = ResolveOperand(&instruction->operands[0], cpu_state, memory, is_instruction_wide);
        ResolvedOperand operand_2 = ResolveOperand(&instruction->operands[1], cpu_state, memory, is_instruction_wide);

        uint16_t result = op(operand_1, operand_2);

        if (do_set_result)
        {
            operand_1.SetValue(result);
        }

        return result;
    }
}
