#ifndef TEXT_OUTPUT_H
#define TEXT_OUTPUT_H

namespace text_output
{
    void PrintAsmString(FILE *output_stream, cpu::instruction::Instruction *instruction);

    void PrintFinalCpuState(FILE *output_stream, cpu::core::CpuState *final_cpu_state);

    void PrintExecutionTrace(FILE *output_stream,
                             cpu::instruction::Instruction *instruction,
                             cpu::core::CpuState *pre_execution_state,
                             cpu::core::CpuState *post_execution_state);
}

#endif // TEXT_OUTPUT_H
