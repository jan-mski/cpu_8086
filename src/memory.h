namespace memory
{
    const uint32_t MEMORY_SIZE = 1024 * 1024;

    struct Memory
    {
        uint8_t bytes[MEMORY_SIZE];

        // not implementing segmented memory access
        uint8_t ReadByte(uint32_t byte_address);

        uint16_t ReadWord(uint32_t byte_1_address);

        void WriteByte(uint32_t byte_address, uint8_t byte_value);

        void WriteWord(uint32_t byte_1_address, uint16_t word_value);
    };

    uint16_t LoadFileToMemory(Memory *memory, const char *file_path);

    void SaveMemoryToFile(const char *file_name, uint16_t offset, Memory *memory);
}
