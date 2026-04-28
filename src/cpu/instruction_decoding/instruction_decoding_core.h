#ifndef CPU_INSTRUCTION_DECODING_CORE_H
#define CPU_INSTRUCTION_DECODING_CORE_H

namespace cpu::instruction_decoding::core
{
    cpu::instruction::Instruction DecodeInstruction(context::DecodingContext *decoding_context,
                                                    cpu::core::CpuState *cpu_state,
                                                    memory::Memory *memory);
}

#endif // CPU_INSTRUCTION_DECODING_CORE_H
