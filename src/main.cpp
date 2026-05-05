#define _CRT_SECURE_NO_WARNINGS

#include "simulator.cpp"

int main(int argc,
         char* argv[])
{
    if (argc == 0)
    {
        fprintf(stderr, "No file specified\n");
    }

    const char* filepath = argv[1];
    ProgramFlags program_flags = 0;

    for (U8 i = 2; i < argc; ++i)
    {
        if (strcmp(argv[i], "--exec") == 0 || strcmp(argv[i], "-e") == 0)
        {
            program_flags |= ProgramFlag_Execute;
        }
        if (strcmp(argv[i], "--dump-memory") == 0 || strcmp(argv[i], "-d") == 0)
        {
            program_flags |= ProgramFlag_DumpMemory;
        }
        if (strcmp(argv[i], "--print-asm") == 0 || strcmp(argv[i], "-pa") == 0)
        {
            program_flags |= ProgramFlag_PrintAsmString;
        }
        if (strcmp(argv[i], "--print-final-state") == 0 || strcmp(argv[i], "-pf") == 0)
        {
            program_flags |= ProgramFlag_PrintFinalState;
        }
        if (strcmp(argv[i], "--print-execution-trace") == 0 || strcmp(argv[i], "-pe") == 0)
        {
            program_flags |= ProgramFlag_PrintExecutionTrace;
        }
    }

    simulator::ExecuteInstructions(
        stdout,
        filepath,
        program_flags);

    return 0;
}
