#ifndef CPU_INSTRUCTION_EXECUTION_UNARY_H
#define CPU_INSTRUCTION_EXECUTION_UNARY_H

namespace cpu::instruction_execution::unary
{
    typedef uint16_t (*UnaryOp)(resolution::ResolvedOperand);

    uint16_t bitwise_not(resolution::ResolvedOperand a);

    uint16_t ExecuteUnaryInstruction(cpu::instruction::Instruction *instruction,
                                     cpu::core::CpuState *cpu_state,
                                     memory::Memory *memory,
                                     bool do_set_result,
                                     UnaryOp op = nullptr);
}

#endif // CPU_INSTRUCTION_EXECUTION_UNARY_H
