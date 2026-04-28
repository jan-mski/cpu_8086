namespace cpu::instruction_execution::unary
{
    using memory::Memory;
    using cpu::core::CpuState;
    using cpu::instruction::Instruction;
    using cpu::instruction_execution::resolution::ResolvedOperand;
    using cpu::instruction_execution::resolution::ResolveOperand;

    uint16_t bitwise_not(ResolvedOperand a)
    {
        return ~a.GetValue();
    }

    uint16_t ExecuteUnaryInstruction(Instruction *instruction,
                                     CpuState *cpu_state,
                                     Memory *memory,
                                     bool do_set_result,
                                     UnaryOp op)
    {
        ResolvedOperand operand = ResolveOperand(&instruction->operands[0], cpu_state, memory, instruction->is_wide);

        uint16_t result = op(operand);

        if (do_set_result)
        {
            operand.SetValue(result);
        }

        return result;
    }
}
