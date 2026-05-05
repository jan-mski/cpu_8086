#ifndef BASE_H
#define BASE_H

typedef int8_t I8;
typedef uint8_t U8;
typedef int16_t I16;
typedef uint16_t U16;
typedef int32_t I32;
typedef uint32_t U32;

typedef U16 ProgramFlags;
enum ProgramFlag {
    ProgramFlag_Execute             = (1 << 0),
    ProgramFlag_DumpMemory          = (1 << 1),
    ProgramFlag_PrintAsmString      = (1 << 2),
    ProgramFlag_PrintFinalState     = (1 << 3),
    ProgramFlag_PrintExecutionTrace = (1 << 4),
};

#endif // BASE_H
