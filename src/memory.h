#ifndef MEMORY_H
#define MEMORY_H

namespace memory
{
    const uint32_t MEMORY_SIZE = 1024 * 1024;

    struct Memory
    {
        static uint16_t LoadFileToMemory(Memory *memory, const char *file_path);

        static void SaveMemoryToFile(const char *file_path, Memory *memory);

        // not implementing segmented memory access
        uint16_t ReadMemory(uint32_t address, bool is_16_bit);

        void WriteMemory(uint32_t address, bool is_16_bit, uint16_t value);

    private:
        uint8_t bytes[MEMORY_SIZE] = {};

        uint8_t ReadByte(uint32_t byte_address);

        uint16_t ReadWord(uint32_t byte_1_address);

        void WriteByte(uint32_t byte_address, uint8_t byte_value);

        void WriteWord(uint32_t byte_1_address, uint16_t word_value);
    };
}

#endif // MEMORY_H
