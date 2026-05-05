#ifndef INSTRUCTION_DECODING_OPERANDS_H
#define INSTRUCTION_DECODING_OPERANDS_H

namespace instruction_decoding::operands
{
    void DecodeOperands(instruction::Instruction* instruction,
                        specs::OperandSpecType* operand_types,
                        context::DecodingContext* decoding_context);
}

#endif // INSTRUCTION_DECODING_OPERANDS_H
