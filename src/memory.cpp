namespace memory
{
    uint8_t Memory::ReadByte(uint32_t byte_address)
    {
        if (byte_address < MEMORY_SIZE)
        {
            return bytes[byte_address];
        }

        return 0;
    }

    uint16_t Memory::ReadWord(uint32_t byte_1_address)
    {
        uint32_t byte_2_address = byte_1_address + 1;
        if (byte_1_address < MEMORY_SIZE && byte_2_address < MEMORY_SIZE)
        {
            return (uint16_t) bytes[byte_1_address] | (uint16_t) (bytes[byte_2_address] << 8);
        }

        return 0;
    }

    void Memory::WriteByte(uint32_t byte_address, uint8_t byte_value)
    {
        if (byte_address < MEMORY_SIZE)
        {
            bytes[byte_address] = byte_value;
        }
    }

    void Memory::WriteWord(uint32_t byte_1_address, uint16_t word_value)
    {
        uint32_t byte_2_address = byte_1_address + 1;
        if (byte_1_address < MEMORY_SIZE && byte_2_address < MEMORY_SIZE)
        {
            bytes[byte_1_address] = (uint8_t) word_value;
            bytes[byte_2_address] = (uint8_t) (word_value >> 8);
        }
    }

    uint16_t LoadFileToMemory(Memory *memory, const char *file_path)
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
}
