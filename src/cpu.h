#define ARRAY_SIZE(array) ((sizeof(array) / sizeof(array[0])))

void DecodeInstructions(FILE *output_stream, FILE *input_stream);
