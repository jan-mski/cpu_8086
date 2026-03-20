#define ARRAY_SIZE(array) ((sizeof(array) / sizeof(array[0])))

namespace cpu::core
{
    void ExecuteInstructions(FILE *output_stream,
                             FILE *input_stream,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace);
}
