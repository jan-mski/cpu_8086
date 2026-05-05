#ifndef INSTRUCTION_DECODING_CORE_H
#define INSTRUCTION_DECODING_CORE_H

namespace instruction_decoding::core
{
    instruction::Instruction DecodeInstruction(context::DecodingContext* decoding_context,
                                               cpu::CpuState* cpu_state,
                                               memory::Memory* memory);
}

#endif // INSTRUCTION_DECODING_CORE_H
