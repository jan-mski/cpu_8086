#define ARRAY_SIZE(array) ((sizeof(array) / sizeof(array[0])))

namespace simulator
{
    void ExecuteInstructions(FILE *output_stream,
                             const char *input_file_path,
                             bool print_asm_strings,
                             bool print_final_state,
                             bool print_execution_trace,
                             bool print_instruction_pointer);
}
