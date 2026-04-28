#ifndef CPU_INSTRUCTION_EXECUTION_BINARY_H
#define CPU_INSTRUCTION_EXECUTION_BINARY_H

namespace cpu::instruction_execution::binary
{
    typedef uint16_t (*BinaryOp)(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t noop(resolution::ResolvedOperand _, resolution::ResolvedOperand b);

    uint16_t add(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t subtract(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t bitwise_and(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t bitwise_or(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t bitwise_xor(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t bitwise_shl(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t bitwise_shr(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t bitwise_sar(resolution::ResolvedOperand a, resolution::ResolvedOperand b);

    uint16_t ExecuteBinaryInstruction(cpu::instruction::Instruction *instruction,
                                      cpu::core::CpuState *cpu_state,
                                      memory::Memory *memory,
                                      bool do_set_result,
                                      BinaryOp op);
}

#endif // CPU_INSTRUCTION_EXECUTION_BINARY_H
