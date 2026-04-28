#ifndef CPU_INSTRUCTION_DECODING_OPERANDS_H
#define CPU_INSTRUCTION_DECODING_OPERANDS_H

namespace cpu::instruction_decoding::operands
{
    void DecodeOperands(cpu::instruction::Instruction *instruction,
                        specs::OperandSpecType *operand_types,
                        uint8_t num_operands,
                        context::DecodingContext *decoding_context);
}

#endif // CPU_INSTRUCTION_DECODING_OPERANDS_H
