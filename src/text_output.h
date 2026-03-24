namespace text_output
{
    void PrintAsmString(FILE *output_stream, cpu::instruction::Instruction *instruction);

    void PrintFinalCpuState(FILE *output_stream, cpu::core::Cpu *final_cpu_state, bool print_instruction_pointer);

    void PrintExecutionTrace(FILE *output_stream,
                             cpu::instruction::Instruction *instruction,
                             cpu::core::Cpu *pre_execution_state,
                             cpu::core::Cpu *post_execution_state,
                             bool print_instruction_pointer);
}
