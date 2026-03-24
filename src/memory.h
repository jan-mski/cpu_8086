namespace memory
{
    const uint32_t MEMORY_SIZE = 1024 * 1024;

    struct Memory
    {
        uint8_t bytes[MEMORY_SIZE];
        uint32_t num_bytes_used;
    };

    void LoadFileToMemory(Memory *memory, const char *file_path);

    size_t ReadByte(uint8_t *destination, uint32_t address, Memory *memory);
}
