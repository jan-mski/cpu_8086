namespace cpu::text_output
{
    void PrintAsmString(FILE *output_stream, cpu::instruction::Instruction *instruction);

    void PrintFinalCpuState(FILE *output_stream, cpu::state::CpuState *final_cpu_state);

    void PrintExecutionTrace(FILE *output_stream,
                             cpu::instruction::Instruction *instruction,
                             cpu::state::CpuState *pre_execution_state,
                             cpu::state::CpuState *post_execution_state);
}
