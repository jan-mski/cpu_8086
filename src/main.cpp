#define _CRT_SECURE_NO_WARNINGS

#include "cpu/cpu_core.cpp"

int main(int argc, char *argv[])
{
    if (argc == 0)
    {
        fprintf(stderr, "No file specified\n");
    }

    const char *filepath = argv[1];
    bool print_asm = false;
    bool print_final_state = false;
    bool print_execution_trace = false;

    for (uint8_t i = 2; i < argc; ++i)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            print_asm = true;
        }
        if (strcmp(argv[i], "-f") == 0)
        {
            print_final_state = true;
        }
        if (strcmp(argv[i], "-e") == 0)
        {
            print_execution_trace = true;
        }
    }

    FILE *file = fopen(filepath, "rb");
    if (file == nullptr)
    {
        printf("Error reading file: %s\n", filepath);
        return 1;
    }

    cpu::core::ExecuteInstructions(
        stdout,
        file,
        print_asm,
        print_final_state,
        print_execution_trace);

    fclose(file);

    return 0;
}
