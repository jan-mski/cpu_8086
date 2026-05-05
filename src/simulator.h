#ifndef SIMULATOR_H
#define SIMULATOR_H

#define ARRAY_SIZE(array) ((sizeof(array) / sizeof(array[0])))

namespace simulator
{
    void ExecuteInstructions(FILE* output_stream,
                             const char* input_file_path,
                             ProgramFlags program_flags);
}

#endif // SIMULATOR_H
