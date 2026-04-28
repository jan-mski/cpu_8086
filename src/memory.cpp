namespace memory
{
    uint16_t Memory::LoadFileToMemory(Memory *memory, const char *file_path)
    {
        FILE *file = fopen(file_path, "rb");

        if (file == nullptr)
        {
            fprintf(stderr, "Error reading file: %s\n", file_path);

            return 0;
        }

        size_t num_bytes_read = fread(memory->bytes, 1, MEMORY_SIZE, file);

        fclose(file);

        return num_bytes_read;
    }

    void Memory::SaveMemoryToFile(const char *file_path, Memory *memory)
    {
        FILE *file = fopen(file_path, "wb");

        if (file == nullptr)
        {
            fprintf(stderr, "Error opening file for writing: %s\n", file_path);
            return;
        }

        fwrite(memory->bytes, 1, MEMORY_SIZE, file);

        fclose(file);
    }

    uint16_t Memory::ReadMemory(uint32_t address, bool is_16_bit)
    {
        return is_16_bit
                   ? ReadWord(address)
                   : ReadByte(address);
    }

    void Memory::WriteMemory(uint32_t address, bool is_16_bit, uint16_t value)
    {
        is_16_bit
            ? WriteWord(address, value)
            : WriteByte(address, (uint8_t) value);
    }

    uint8_t Memory::ReadByte(uint32_t byte_address)
    {
        byte_address = byte_address < MEMORY_SIZE ? byte_address : 0;

        return bytes[byte_address];
    }

    uint16_t Memory::ReadWord(uint32_t byte_1_address)
    {
        return (uint16_t) ReadByte(byte_1_address)
               | (uint16_t) (ReadByte(byte_1_address + 1) << 8);
    }

    void Memory::WriteByte(uint32_t byte_address, uint8_t byte_value)
    {
        byte_address = byte_address < MEMORY_SIZE ? byte_address : 0;
        bytes[byte_address] = byte_value;
    }

    void Memory::WriteWord(uint32_t byte_1_address, uint16_t word_value)
    {
        WriteByte(byte_1_address, (uint8_t) word_value);
        WriteByte(byte_1_address + 1, (uint8_t) (word_value >> 8));
    }
}
