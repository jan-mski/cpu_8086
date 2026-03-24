#define _CRT_SECURE_NO_WARNINGS

#include "simulator.cpp"

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
    bool print_instruction_pointer = false;

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
        if (strcmp(argv[i], "-i") == 0)
        {
            print_instruction_pointer = true;
        }
    }

    simulator::ExecuteInstructions(
        stdout,
        filepath,
        print_asm,
        print_final_state,
        print_execution_trace,
        print_instruction_pointer);

    return 0;
}
