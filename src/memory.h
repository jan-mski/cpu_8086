#ifndef MEMORY_H
#define MEMORY_H

namespace memory
{
    typedef U32 Address;

    const U32 MEMORY_SIZE = 1024 * 1024;

    struct Memory
    {
        U8 bytes[MEMORY_SIZE] = {};
    };

    U8 ReadByte(Memory* memory,
                Address byte_address);

    void WriteByte(Memory* memory,
                   Address byte_address,
                   U8 byte_value);

    U16 ReadWord(Memory* memory,
                 Address byte_1_address);

    void WriteWord(Memory* memory,
                   Address byte_1_address,
                   U16 word_value);

    U16 LoadFileToMemory(Memory* memory,
                         const char* file_path);

    void SaveMemoryToFile(const char* file_path,
                          Memory* memory);
}

#endif // MEMORY_H
