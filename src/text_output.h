#ifndef TEXT_OUTPUT_H
#define TEXT_OUTPUT_H

namespace text_output
{
    void PrintAsmString(FILE* output_stream,
                        instruction::Instruction* instruction);

    void PrintFinalCpuState(FILE* output_stream,
                            cpu::CpuState* final_cpu_state);

    void PrintExecutionTrace(FILE* output_stream,
                             instruction::Instruction* instruction,
                             cpu::CpuState* pre_execution_state,
                             cpu::CpuState* post_execution_state,
                             cycle_estimation::CycleCountEstimate cycle_count_estimate);
}

#endif // TEXT_OUTPUT_H
