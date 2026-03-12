#define ARRAY_SIZE(array) ((sizeof(array) / sizeof(array[0])))

void ExecuteInstructions(FILE *output_stream,
                         FILE *input_stream,
                         bool print_instruction_strings,
                         bool print_register_values);
